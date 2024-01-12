#include<bits/stdc++.h>
#include <cstdio>
#include <fstream>
#include <unistd.h>
#include"users.h"
using namespace std;
map<string,bool>in_log;
struct info_log{
  string id;
  users user;
  int book_pos;
};
vector<info_log>lg;
string getword(string s,int &st){
  int l=s.length();
  string ans;
  while(st<l){
    if(s[st]!=' ') break;
    st++;
  }
  while(st<l){
    if(s[st]==' ') break;
    ans+=s[st];
    st++;
  }
  return ans;
}
bool is_userid(string s){
  if(s.length()==0) return false;
  for(int i=0;i<s.length();i++){
    if(s[i]>='0'&&s[i]<='9');
    else if(s[i]>='a'&&s[i]<='z');
    else if(s[i]>='A'&&s[i]<='Z');
    else if(s[i]=='_');
    else return false;
  }
  return true;
}
bool is_ascll(string s){
  if(s.length()==0) return false;
  for(int i=0;i<s.length();i++){
    if(s[i]<33||s[i]>126) return false;
  }
  return true;
}
bool is_book_name(string s){
  if(!is_ascll(s)) return false;
  for(int i=0;i<s.length();i++){
    if(s[i]=='"') return false;
  }
  return true;
}
bool is_one_key(string s){
  if(!is_ascll(s)) return false;
  for(int i=0;i<s.length();i++){
    if(s[i]=='"') return false;
    if(s[i]=='|') return false;
  }
  return true;
}
string get(string s,int l,int r){
  string ans;
  if(s.length()<=r) return ans;
  for(int i=l;i<=r;i++){
    ans+=s[i];
  }
  return ans;
}
bool about_isbn(string word){
  string isbn=get(word,6,word.length()-1);
  if(!is_ascll(isbn)){
    return false;
  }
  return true;
}
bool about_name(string word){
  if(word[6]!='"'||word[word.length()-1]!='"'){
    return false;
  }
  string name=get(word,7,word.length()-2);
  if(!is_book_name(name)){
    return false;
  }
  return true;
}
bool about_author(string word){
  if(word[8]!='"'||word[word.length()-1]!='"'){
    return false;
  }
  string author=get(word,9,word.length()-2);
  if(!is_book_name(author)){
    return false;
  }
  return true;
}
int into_int(string s){
  if(!is_ascll(s)) return false;
  int l=s.length(),ans=0;
  for(int i=0;i<l;i++){
    if(s[i]>='0'&&s[i]<='9'){
      ans=ans*10+s[i]-'0';
    }
    else return -1;
  }
  return ans;
}
double into_double(string s){
  if(!is_ascll(s)) return false;
  int l=s.length();
  int ans=0,_ans=0;
  for(int i=0;i<l;i++){
    if(s[i]=='.'){
      string a,b;
      for(int j=0;j<i;j++) a+=s[j];
      ans=into_int(a);
      if(ans==-1) return -1;
      for(int j=i+1;j<l;j++) b+=s[j];
      _ans=into_int(b);
      if(_ans==-1) return -1;
      break;
    }
  }
  double fans=_ans;
  while(fans>0) fans/=10;
  fans+=ans;
  return fans;
}
void debug(){
  fstream file;
  file.open("info_users_summary.db",std::fstream::in|std::fstream::out|std::fstream::binary);
  file.seekg(0);
  int num=-1;
  file.read(reinterpret_cast<char*>(&num),sizeof(int));
  printf("debug:%d",num);
  file.close();
  return ;
}
int main(){
//  freopen("bookstore-testcases/basic/testcase4.in","r",stdin);
//  freopen("test.out","w",stdout);
  fstream file;
  file.open("information/info_users.db",std::fstream::in|std::fstream::out|std::fstream::binary);
  if(!file.is_open()){
    int num=0;
    file.open("information/info_users.db",std::ios::out);
    file.close();
    file.open("information/info_users_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/info_books.db",std::ios::out);
    file.close();
    file.open("information/info_books_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/info_finance.db",std::ios::out);
    file.close();
    file.open("information/info_finance_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/book_name.db",std::ios::out);
    file.close();
    file.open("information/book_name_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/book_author.db",std::ios::out);
    file.close();
    file.open("information/book_author_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/book_key.db",std::ios::out);
    file.close();
    file.open("information/book_key_summary.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();

    file.open("information/info_steady.db",std::ios::out);
    file.write(reinterpret_cast<char*>(&num),sizeof(int));
    file.close();
    file.open("information/tot_work.db",std::ios::out);
    file.close();
    file.open("information/workers.db",std::ios::out);
    file.close();
    file.open("information/finance.db",std::ios::out);
    file.close();

    
    string name="root",password="sjtu";
    users root(name,password,name,7);
    files <users,users_block,users_summary>f("information/info_users");
    f.insert(root);

  }
  else file.close();
  users cur=users();
  string s;
//  debug();
  while(true){
    getline(cin,s);
    if(cin.eof()){
      break;
    }
  //  cout<<s<<endl;
    int p=0;
    string word=getword(s,p);
    if(word=="su"){
      string id,password;
      id=getword(s,p);
      if(!is_userid(id)){
        printf("Invalid\n");
        continue;
      }
      password=getword(s,p);
      if(!is_userid(password)){
        printf("Invalid\n");
        continue;
      }
      if(password==""){
        if(!cur.su(String(id))){
          printf("Invalid\n");
        }
        else{
          lg.push_back((info_log){id,cur,0});
          in_log[id]=true;
        }
        continue;
      }
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!cur.su(id,password)){
        printf("Invalid\n");
        continue;
      }
      else{
        lg.push_back((info_log){id,cur,0});
        in_log[id]=true;
      }
    }
    else if(word=="logout"){
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(lg.size()==0){
        printf("Invalid\n");
        continue;
      }
      if(!cur.logout()){
        printf("Invalid\n");
        continue;
      }
      in_log.erase(lg.back().id);
      lg.pop_back();
      if(lg.size()!=0)
        cur=lg.back().user;
      else cur=users();
    }
    else if(word=="register"){
      string id,password,name;
      id=getword(s,p);
      if(!is_userid(id)){
        printf("Invalid\n");
        continue;
      }
      password=getword(s,p);
      if(!is_userid(password)){
        printf("Invalid\n");
        continue;
      }
      name=getword(s,p);
      if(!is_ascll(name)){
        printf("Invalid\n");
        continue;
      }
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!cur.register_user(id,password,name)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="passwd"){
      string id,cur_pass,new_pass;
      id=getword(s,p);
      if(!is_userid(id)){
        printf("Invalid\n");
        continue;
      }
      cur_pass=getword(s,p);
      if(!is_userid(cur_pass)){
        printf("Invalid\n");
        continue;
      }
      new_pass=getword(s,p);
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(new_pass==""){
        if(!cur.change_pass(id,cur_pass)){
          printf("Invalid\n");
          continue;
        }
      }
      else{
        if(!is_userid(new_pass)){
          printf("Invalid\n");
          continue;
        }
        if(!cur.change_pass(id,cur_pass,new_pass)){
          printf("Invalid\n");
          continue;
        }
      }

    }
    else if(word=="useradd"){
      string id,password,name,pri;
      id=getword(s,p);
      if(!is_userid(id)){
        printf("Invalid\n");
        continue;
      }
      password=getword(s,p);
      if(!is_userid(password)){
        printf("Invalid\n");
        continue;
      }
      pri=getword(s,p);
      int pr=into_int(pri);
      if(pr==-1||(pr!=1&&pr!=3&&pr!=7)){
        printf("Invalid\n");
        continue;
      }
      name=getword(s,p);
      if(!is_ascll(name)){
        printf("Invalid\n");
        continue;
      }
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!cur.useradd(id,password,pr,name)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="delete"){
      string id=getword(s,p);
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!is_userid(id)){
        printf("Invalid\n");
        continue;
      }
      if(in_log.find(id)!=in_log.end()){
        printf("Invalid\n");
        continue;
      }
      if(!cur.del(id)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="show"){
      word=getword(s,p);
      if(word=="finance"){
        word=getword(s,p);
        if(word==""){
          int cnt;
          file.open("size.db",fstream::in|fstream::out|fstream::binary);
          file.seekg(sizeof(int)*2);
          file.read(reinterpret_cast<char*>(&cnt),sizeof(int));
          file.close();
          if(!cur.show_finance(cnt)){
            printf("Invalid\n");
            continue;
          }
        }
        else{
          if(getword(s,p)!=""){    
            printf("Invalid\n");
            continue;
          }
          int cnt=into_int(word);
          if(cnt==-1){
            printf("Invalid\n");
            continue;
          }
          if(!cur.show_finance(cnt)){
            printf("Invalid\n");
            continue;
          }
        }
      }
      else if(word==""){
        if(!cur.show(0,word)){
          printf("Invalid\n");
          continue;
        }
      }
      else{
        if(getword(s,p)!=""){
          printf("Invalid\n");
          continue;
        }
        if(get(word,0,5)=="-ISBN="){
          if(!about_isbn(word)){
            printf("Invalid\n");
            continue;
          }
          string isbn=get(word,6,word.length()-1);
          if(!cur.show(1,isbn)){            
            printf("Invalid\n");
            continue;
          }
        }
        else if(get(word,0,5)=="-name="){
          if(!about_name(word)){
            printf("Invalid\n");
            continue;
          }
          string name=get(word,7,word.length()-2);
          if(!cur.show(2,name)){
            printf("Invalid\n");
            continue;
          }
        }
        else if(get(word,0,7)=="-author="){
          if(!about_author(word)){
            printf("Invalid\n");
            continue;
          }
          string author=get(word,9,word.length()-2);
          if(!cur.show(3,author)){
            printf("Invalid\n");
            continue;
          }
        }
        else if(get(word,0,8)=="-keyword="){
          if(word[9]!='"'||word[word.length()-1]!='"'){
            printf("Invalid\n");
            continue;
          }
          string keys=get(word,10,word.length()-2);
          if(!is_one_key(keys)){
            printf("Invalid\n");
            continue;
          }
          if(!cur.show(4,keys)){
            printf("Invalid\n");
            continue;
          }
        }
        else{
          printf("Invalid\n");
          continue;
        }
      }
    }
    else if(word=="buy"){
      string isbn,cnt;
      isbn=getword(s,p);
      if(!is_ascll(isbn)){
        printf("Invalid\n");
        continue;
      }
      cnt=getword(s,p);
      int c=into_int(cnt);
      if(c==-1){
        printf("Invalid\n");
        continue;
      }
      if(!cur.buy(isbn,c)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="select"){
      string isbn=getword(s,p);
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!is_ascll(isbn)){
        printf("Invalid\n");
        continue;
      }
      int num=lg.size();
      if(num==0){
        printf("Invalid\n");
        continue;
      }
      if(!cur.select(isbn,lg[num-1].book_pos)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="modify"){
      if(!cur.have_pri(3)){
        printf("Invalid\n");
        continue;
      }
      if(lg.back().book_pos==0){
        printf("Invalid\n");
        continue;
      }
    //  cout<<s<<endl;
      books b;
      file.open("information/info_steady.db",fstream::in|fstream::out|fstream::binary);
      file.seekg(sizeof(int)+sizeof(books)*(lg.back().book_pos-1));
      file.read(reinterpret_cast<char*>(&b),sizeof(books));
      file.close();

      word=getword(s,p);
      if(word==""){
        printf("Invalid\n");
        continue;
      }
      bool vis[10]={false,false,false,false,false};
      while(word!=""){
        if(get(word,0,5)=="-ISBN="){
          if(vis[0]) break;
          vis[0]=true;
          if(!about_isbn(word)) break;
          string isbn=get(word,6,word.length()-1);
          if(b.is_index(isbn)){
            break;
          }
        }
        else if(get(word,0,5)=="-name="){
          if(vis[1]) break;
          vis[1]=true;
          if(!about_name(word)) break;
        }
        else if(get(word,0,7)=="-author="){
          if(vis[2]) break;
          vis[2]=true;
          if(!about_author(word)) break;
        }
        else if(get(word,0,8)=="-keyword="){
          if(vis[3]) break;
          vis[3]=true;
          if(word[9]!='"'||word[word.length()-1]!='"'){
            printf("Invalid\n");
            continue;
          }
          string keys=get(word,10,word.length()-2);
          if(!is_book_name(keys)){
            printf("Invalid\n");
            continue;
          }
          map<string,bool>vis;
          string k;
          for(int i=0;i<keys.length();i++){
            if(keys[i]=='|'){
              if(vis.find(k)!=vis.end()){
                break;
              }
              vis[k]=true;
              k="";
            }
            k+=keys[i];
          }
          if(vis.find(k)!=vis.end()) break;
        }
        else if(get(word,0,6)=="-price="){
          if(vis[4]) break;
          vis[4]=true;
          double price=into_double(get(word,7,word.length()-1));
          if(price<0) break;
        }
        else{
          break;
        }
        word=getword(s,p);
      }
      if(word!=""){
        printf("Invalid\n");
        continue;
      }
    //  cout<<s<<endl;
      p=0;
      word=getword(s,p);
      word=getword(s,p);
      while(word!=""){
        if(get(word,0,5)=="-ISBN="){
          string isbn=get(word,6,word.length()-1);
        //  cout<<s<<"ASA"<<endl;
        //  cout<<isbn<<'\n';
        //  cout<<b.get_index().into_string()<<'\n';
          cur.modify(0,isbn,b);
        }
        else if(get(word,0,5)=="-name="){
          string name=get(word,7,word.length()-2);
          cur.modify(1,name,b);
        }
        else if(get(word,0,7)=="-author="){
          string author=get(word,9,word.length()-2);
          cur.modify(2,author,b);
        }
        else if(get(word,0,8)=="-keyword="){
          string keys=get(word,10,word.length()-2);
          string k;String ke[65];int num=0;
          for(int i=0;i<keys.length();i++){
            if(keys[i]=='|'){
              ke[++num]=String(k);
              k="";
            }
            k+=keys[i];
          }
          ke[++num]=String(k);
          cur.modify(ke,num,b);
        }
        else if(get(word,0,6)=="-price="){
          double price=into_double(get(word,7,word.length()-1));
          cur.modify(price,b);
        }
        word=getword(s,p);
      }
    }
    else if(word=="import"){
      if(lg.back().book_pos==0){
        printf("Invalid\n");
        continue;
      }
      books b;
      file.open("information/info_book.db",fstream::in|fstream::out|fstream::binary);
      file.seekg(sizeof(books)*(lg.back().book_pos-1));
      file.read(reinterpret_cast<char*>(&b),sizeof(books));
      file.close();
      int num=into_int(getword(s,p));
      if(num==-1){
        printf("Invalid\n");
        continue;
      }
      double cos=into_double(getword(s,p));
      if(cos<0){
        printf("Invalid\n");
        continue;
      }
      if(getword(s,p)!=""){  
        printf("Invalid\n");
        continue;
      }
      if(!cur.import(num,cos,b)){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="report"){
      word=getword(s,p);
      if(word=="finance"){
        if(getword(s,p)!=""){
          printf("Invalid\n");
          continue;
        }
        if(!cur.report_finance()){
          printf("Invalid\n");
          continue;
        }
      }
      else if(word=="employee"){
        if(getword(s,p)!=""){
          printf("Invalid\n");
          continue;
        }
        if(!cur.report_employee()){
          printf("Invalid\n");
          continue;
        }
      }
      else{
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="log"){
      if(getword(s,p)!=""){
        printf("Invalid\n");
        continue;
      }
      if(!cur.log()){
        printf("Invalid\n");
        continue;
      }
    }
    else if(word=="quit"){
      break;
    }
    else if(word=="exit"){
      break;
    }
    else if(word==""){
      continue;
    }
    else {
      printf("Invalid\n");
    }
  }
  return 0;
}