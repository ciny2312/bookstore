#include<iostream>
#include<fstream>
#include<algorithm>
#include<cmath>
const int N=500,block_N=500;
using std::string;
std::fstream f1,f2,f3;
struct data{
  string index;
  int val;
  bool operator < (const data &x){
    if(index!=x.index) return index<x.index;
    return val<x.val;
  }
  bool operator == (const data &x){
    return val==x.val&&index==x.index;
  }
};
struct summary{
  data fir;
  int pos,nxt;
};
struct block{
    int nxt,len;
    data a[block_N+5];
};
void debug(){
  f1.seekg(0);
  summary all;
  f1.read(reinterpret_cast<char*>(&all),sizeof(summary));
  std::cout<<"all:"<<all.pos<<' '<<all.nxt<<' '<<all.fir.index;
  std::cout<<std::endl;
}

int main(){
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  int x=0;
  f3.open("info.in",std::ios::out);
  f3.write(reinterpret_cast<char *>(&x),sizeof(int));
  f3.write(reinterpret_cast<char *>(&x),sizeof(int));
  f3.close();
  f1.open("summary.in",std::ios::out);
  f1.close();
  f2.open("block.in",std::ios::out);
  f2.close();
  int n;scanf("%d",&n);
    string op,index;
    std::cin>>op>>index;
    if(op=="insert"){
      int x;
      scanf("%d",&x);
      data cur;cur.val=x;cur.index=index;
      summary all;all.fir=cur;all.pos=1;all.nxt=0;
      f1.open("summary.in",std::fstream::in|std::fstream::out|std::fstream::binary);
      f1.seekp(0);
      f1.write(reinterpret_cast<char *>(&all),sizeof(summary));

      debug();
      f1.close();
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