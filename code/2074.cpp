#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
const int N=500,block_N=500;
using std::string;
std::fstream f1,f2,f3;
struct datam{
  char index[70];
  int val,len;
  bool operator < (const datam &x) const{
    for(int i=0;i<std::min(len,x.len);i++){
      if(index[i]<x.index[i]) return 1;
      if(index[i]>x.index[i]) return 0;
    }
    if(len<x.len) return 1;
    if(len>x.len) return 0;
    return val<x.val;
  }
  bool operator == (const datam &x){
    if(len!=x.len) return 0;
    for(int i=0;i<len;i++){
      if(index[i]!=x.index[i]) return 0;
    }
    return val==x.val;
  }
};
struct summary{
  datam fir;
  int pos,nxt;
};
struct block{
    int nxt,len;
    datam a[block_N+5];
};
void debug(){
  f1.seekg(0);
  summary all;
  f1.read(reinterpret_cast<char*>(&all),sizeof(summary));
  std::cout<<"all:"<<all.pos<<' '<<all.nxt<<' '<<all.fir.len<<' ';
  for(int i=0;i<all.fir.len;i++)
    std::cout<<all.fir.index[i];
  std::cout<<std::endl;
}
void divide(int rk,block x){
  int num;
  f3.seekg(sizeof(int));
  f3.read(reinterpret_cast<char*>(&num),sizeof(int));
  num++;
  f3.seekp(sizeof(int));
  f3.write(reinterpret_cast<char*>(&num),sizeof(int));
//  debug();
  block y;y.len=x.len/2;
  x.len=x.len-y.len;
  for(int i=x.len+1;i<=x.len+y.len;i++){
    y.a[i-x.len]=x.a[i];
  }
  y.nxt=x.nxt;x.nxt=num;
  f2.seekp(sizeof(block)*(rk-1));
  f2.write(reinterpret_cast<char *>(&x),sizeof(block));
  f2.seekp(0,std::ios::end);
  f2.write(reinterpret_cast<char *>(&y),sizeof(block));
//  debug();
  summary all,nxt_all;
  f1.seekg(sizeof(summary)*(rk-1));
  f1.read(reinterpret_cast<char*>(&all),sizeof(summary));
  nxt_all.fir=y.a[1];
  nxt_all.nxt=all.nxt;
  all.nxt=num;
  nxt_all.pos=num;
  f1.seekp(sizeof(summary)*(rk-1));
  f1.write(reinterpret_cast<char *>(&all),sizeof(summary));
  f1.seekp(0,std::ios::end);
  f1.write(reinterpret_cast<char *>(&nxt_all),sizeof(summary));
//  debug();
  
}
void merge(int rk,block x,block y){
  for(int i=1;i<=y.len;i++){
    x.a[i+x.len]=y.a[i];
  }
  x.len+=y.len;x.nxt=y.nxt;
  f2.seekp(sizeof(block)*(rk-1));
  f2.write(reinterpret_cast<char*>(&x),sizeof(block));
  summary all,nxt_all;
  f1.seekg(sizeof(summary)*(rk-1));
  f1.read(reinterpret_cast<char*>(&all),sizeof(summary));
  f1.seekg(sizeof(summary)*(all.nxt-1));
  f1.read(reinterpret_cast<char*>(&nxt_all),sizeof(summary));
  all.nxt=nxt_all.nxt;
  all.fir=x.a[1];
  f1.seekp(sizeof(summary)*(rk-1));
  f1.write(reinterpret_cast<char*>(&all),sizeof(summary));
}
void insert_in_block(int rk,datam cur){
  f2.open("block.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f2.seekg(sizeof(block)*(rk-1));
  block b;f2.read(reinterpret_cast<char *>(&b),sizeof(block));
  if(b.len==0||cur<b.a[1]){
    for(int i=b.len;i>=1;i--){
      b.a[i+1]=b.a[i];
    }
    b.a[1]=cur;b.len++;
    summary all;
    f1.seekg(sizeof(summary)*(rk-1));
    f1.read(reinterpret_cast<char *>(&all),sizeof(summary));
    all.fir=b.a[1];
    f1.seekp(sizeof(summary)*(rk-1));
    f1.write(reinterpret_cast<char *>(&all),sizeof(summary));
  }
  else{
    for(int i=b.len;i>=1;i--){
      if(b.a[i]<cur){
        for(int j=b.len;j>i;j--){
          b.a[j+1]=b.a[j];
        }
        b.a[i+1]=cur;b.len++;
        break;
      }
    }
  }
  if(b.len>block_N) divide(rk,b);
  else{
    f2.seekp(sizeof(block)*(rk-1));
    f2.write(reinterpret_cast<char *>(&b),sizeof(block));
  }
  f2.close();
}
void insert(string s,int x){
  summary all,nxt_all;
  datam cur;cur.val=x;cur.len=s.length();
  for(int i=0;i<s.length();i++) cur.index[i]=s[i];
  f3.open("info.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f1.open("summary.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f3.seekg(0);
  int head;f3.read(reinterpret_cast<char*>(&head),sizeof(int));
  if(head==0){
    int x=1;
    f3.seekp(0);
    f3.write(reinterpret_cast<char*>(&x),sizeof(int));
    f3.write(reinterpret_cast<char*>(&x),sizeof(int));

    all.nxt=0;all.pos=1;all.fir=cur;
    f1.seekp(0);
    f1.write(reinterpret_cast<char*>(&all),sizeof(summary));
  //  debug();
    f2.open("block.in",std::fstream::in|std::fstream::out|std::fstream::binary);
    block b;b.nxt=0;b.len=1;b.a[1]=cur;
    f2.seekp(0);
    f2.write(reinterpret_cast<char*>(&b),sizeof(block));
    f1.close();f2.close();f3.close();
    return ;
  }
  f1.seekg(sizeof(summary)*(head-1));
  f1.read(reinterpret_cast<char *>(&all),sizeof(summary));
  while(true){
    if(all.nxt==0){
      insert_in_block(all.pos,cur);
      break;
    }
    f1.seekg(sizeof(summary)*(all.nxt-1));
    f1.read(reinterpret_cast<char *>(&nxt_all),sizeof(summary));
    if(cur<nxt_all.fir){
      insert_in_block(all.pos,cur);
      break;
    }
    all=nxt_all;
  }
  f1.close();f3.close();
}
void del_in_block(int rk,datam cur){
  f2.open("block.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f2.seekg(sizeof(block)*(rk-1));
  block b;f2.read(reinterpret_cast<char *>(&b),sizeof(block));
  if(cur==b.a[1]){
    summary all;f1.seekg(sizeof(summary)*(rk-1));
    f1.read(reinterpret_cast<char *>(&all),sizeof(summary));
    all.fir=b.a[2];
    f1.seekp(sizeof(summary)*(rk-1));
    f1.write(reinterpret_cast<char *>(&all),sizeof(summary));
  }
  for(int i=1;i<=b.len;i++){
    if(cur==b.a[i]){
      for(int j=i;j<b.len;j++){
        b.a[j]=b.a[j+1];
      }
      b.len--;
      break;
    }
  }
  if(b.nxt==0){
    f2.seekp(sizeof(block)*(rk-1));
    f2.write(reinterpret_cast<char *>(&b),sizeof(block));
    f2.close();
    return ;
  }
  block nxt_b;f2.seekg(sizeof(block)*(b.nxt-1));
  f2.read(reinterpret_cast<char*>(&nxt_b),sizeof(block));
  if(b.len+nxt_b.len<=block_N){
    merge(rk,b,nxt_b);
  }
  else{
    f2.seekp(sizeof(block)*(rk-1));
    f2.write(reinterpret_cast<char *>(&b),sizeof(block));
  }
  f2.close();
}
void del(string s,int x){
  f3.open("info.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f3.seekg(0);
  int head;f3.read(reinterpret_cast<char*>(&head),sizeof(int));
  if(head==0){
    f3.close();
    return;
  }
  f1.open("summary.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  summary all,nxt_all;f1.seekg(sizeof(summary)*(head-1));
  f1.read(reinterpret_cast<char *>(&all),sizeof(summary));

  datam cur;cur.val=x;cur.len=s.length();
  for(int i=0;i<s.length();i++) cur.index[i]=s[i];
  while(true){
    if(all.nxt==0){
      del_in_block(all.pos,cur);
      break;
    }
    f1.seekg(sizeof(summary)*(all.nxt-1));
    f1.read(reinterpret_cast<char *>(&nxt_all),sizeof(summary));
    if(cur<nxt_all.fir){
      del_in_block(all.pos,cur);
      break;
    }
    all=nxt_all;
  }
  f1.close();f3.close();
}
bool smaller(char *x,int xlen,char *y,int ylen){
  for(int i=0;i<std::min(xlen,ylen);i++){
      if(x[i]<y[i]) return 1;
      if(x[i]>y[i]) return 0;
    }
    if(xlen<ylen) return 1;
    return 0;
}
bool smaller_equal(char *x,int xlen,char *y,int ylen){
  for(int i=0;i<std::min(xlen,ylen);i++){
      if(x[i]<y[i]) return 1;
      if(x[i]>y[i]) return 0;
    }
    if(xlen<=ylen) return 1;
    return 0;
}
bool equal(char *x,int xlen,char *y,int ylen){
    if(xlen!=ylen) return 0;
    for(int i=0;i<ylen;i++){
      if(x[i]!=y[i]) return 0;
    }
    return 1;
}
void find(string s){
  f1.open("summary.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f2.open("block.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  f3.open("info.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  datam cur;cur.val=0;cur.len=s.length();
  for(int i=0;i<s.length();i++) cur.index[i]=s[i];
  summary all,nxt_all;
  block b;int head,cnt=0;
  f3.seekg(0);
  f3.read(reinterpret_cast<char*>(&head),sizeof(int));
  if(head==0){
    printf("null\n");
    f1.close();
    f2.close();
    f3.close();
    return ;
  }
//  debug();
  f1.seekg(sizeof(summary)*(head-1));
  f1.read(reinterpret_cast<char *>(&all),sizeof(summary));
  while(true){
    if(smaller(cur.index,cur.len,all.fir.index,all.fir.len)) break;
    if(all.nxt==0){
      f2.seekg(sizeof(block)*(all.pos-1));
      f2.read(reinterpret_cast<char*>(&b),sizeof(block));
      for(int i=1;i<=b.len;i++){
        if(smaller(cur.index,cur.len,b.a[i].index,b.a[i].len)) break;
        if(equal(cur.index,cur.len,b.a[i].index,b.a[i].len)){
          printf("%d ",b.a[i].val);
          cnt++;
        }
      }
      break;
    }
    f1.seekg(sizeof(summary)*(all.nxt-1));
    f1.read(reinterpret_cast<char*>(&nxt_all),sizeof(summary));
    if(smaller_equal(all.fir.index,all.fir.len,cur.index,cur.len)&&
    smaller_equal(cur.index,cur.len,nxt_all.fir.index,nxt_all.fir.len)){
      f2.seekg(sizeof(block)*(all.pos-1));
      f2.read(reinterpret_cast<char*>(&b),sizeof(block));
      for(int i=1;i<=b.len;i++){
        if(smaller(cur.index,cur.len,b.a[i].index,b.a[i].len)) break;
        if(equal(cur.index,cur.len,b.a[i].index,b.a[i].len)){
          printf("%d ",b.a[i].val);
          cnt++;
        }
      }
    }
    all=nxt_all;
  }
  if(cnt==0) printf("null");
  printf("\n");
  f1.close();f2.close();f3.close();
}
int main(){
//  freopen("a.in","r",stdin);
//  freopen("a.out","w",stdout);

  f3.open("info.in",std::fstream::in|std::fstream::out|std::fstream::binary);
  if(!f3.is_open()){
    int x=0;
    f3.open("info.in",std::ios::out);
    f3.write(reinterpret_cast<char *>(&x),sizeof(int));
    f3.write(reinterpret_cast<char *>(&x),sizeof(int));
    f3.close();
    f1.open("summary.in",std::ios::out);
    f1.close();
    f2.open("block.in",std::ios::out);
    f2.close();
  }
  else f3.close();
  int n;
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    string op,index;
    std::cin>>op>>index;
    if(op=="insert"){
      int x;
      scanf("%d",&x);
      insert(index,x);
    }
    else if(op=="delete"){
      int x;
      scanf("%d",&x);
      del(index,x);
    }
    else{
      find(index);
    }
  }
  return 0;
}

/*
8
insert FlowersForAlgernon 1966
insert CppPrimer 2012
insert Dune 2021
insert CppPrimer 2001
find CppPrimer
find Java
delete Dune 2021
find Dune
*/