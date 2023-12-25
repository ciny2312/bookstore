#include <fstream>
#include <ios>
#include<iostream>
#include <sys/select.h>
#include"books.h"


class users{
  String id,name,password;
  int pri,pos;
  public:
  users(String _id=String(),String _password=String(),String _name=String(),int _pri=0){
    id=_id;password=_password;
    name=_name;pri=_pri;
  }
  bool operator<(const users x) const {
    return id<x.id;
  }
  bool operator == (const users x) const {
    return id==x.id;
  }
  bool operator <= (const users x) const {
    return id<=x.id;
  }

  bool is_index(String _id){
    return id==_id;
  }
  String get_index(){
    return id;
  }
  int get_pos(){
    return pos;
  }
  bool register_user(String _id,String _password,String _name);
  bool su(String _id);
  bool su(String _id,String _password);

  bool show(int ty,String index);
  bool buy(String _id,int num);
  bool logout();
  bool change_pass(String _id,String cur_pass,String new_pass);
  bool change_pass(String _id,String new_pass);
  bool useradd(String _id,String _password,int _pri,String _name);
  bool select(String ISBN,int &book_pos);
  bool have_pri(int p);
  bool modify(int ty,String index,books b);
  bool modify(String *keys,int num,books b);
  bool modify(double price,books b);
  bool import(int num,double cost,books b);
  bool del(String _id);
  bool show_finance(int num);
  bool report_finance();
  bool report_employee();
  bool log();
};

class users_block{
  public:
  users a[N+50];
  int len,nxt;
};

class users_summary{
  public:
  users fir;
  int pos,nxt;
};

class finance_block{
  public:
  double a[N+50],tot;
  int len;
};
class finance_summary{
  public:
  double tot;
  int len;
};
class finance{
  public:
  void insert(double money){
    std::fstream f,f_summary;
    f.open("info_finance.db",std::fstream::in|std::fstream::out|std::fstream::binary);
    f_summary.open("info_finance_summary.db",std::fstream::in|std::fstream::out|std::fstream::binary);
    finance_block b;
    f.seekg(sizeof(finance_block),std::ios::end);
    f.read(reinterpret_cast<char*>(&b),sizeof(finance_block));
    if(b.len==N){
      finance_block nw;
      nw.len=1;
      nw.a[1]=nw.tot=money;
      f.seekp(0,std::ios::end);
      f.write(reinterpret_cast<char*>(&nw),sizeof(finance_block));
      finance_summary all;
      all.len=nw.len;all.tot=nw.tot;
      f_summary.seekp(0,std::ios::end);
      f_summary.write(reinterpret_cast<char*>(&all),sizeof(finance_summary));
    }
    else{
      b.a[++b.len]=money;
      b.tot+=money;
      f.seekp(sizeof(finance_block),std::ios::end);
      f.write(reinterpret_cast<char*>(&b),sizeof(finance_block));
      finance_summary all;
      all.len=b.len;all.tot=b.tot;
      f_summary.seekp(sizeof(finance_summary),std::ios::end);
      f_summary.write(reinterpret_cast<char*>(&all),sizeof(finance_summary));
    }
    f_summary.seekg(0);int num;
    f_summary.read(reinterpret_cast<char*>(&num),sizeof(int));
    f_summary.seekp(0);num++;
    f_summary.write(reinterpret_cast<char*>(&num),sizeof(int));
    f.close();f_summary.close();
  }
  bool show(int _num){
    if(_num==0){
      printf("\n");
      return true;
    }
    std::fstream f,f_summary;
    f.open("info_finance.db",std::fstream::in|std::fstream::out|std::fstream::binary);
    f_summary.open("info_finance_summary.db",std::fstream::in|std::fstream::out|std::fstream::binary);
    f_summary.seekg(0);int num;
    f_summary.read(reinterpret_cast<char*>(&num),sizeof(int));
    if(num<_num){
      f.close();f_summary.close();
      return false;
    }
    int cnt=1;double ans1=0,ans2=0;
    finance_summary all;
    while(_num>0){
      f_summary.seekg(cnt*sizeof(finance_summary),std::ios::end);
      f_summary.read(reinterpret_cast<char*>(&all),sizeof(finance_summary));
      if(all.len>_num){
        finance_block b;
        f.seekg(cnt*sizeof(finance_block),std::ios::end);
        f.read(reinterpret_cast<char*>(&b),sizeof(finance_block));
        for(int i=b.len;i>=1;i--){
          if(b.a[i]>0) ans1+=b.a[i];
          else ans2+=b.a[i];
          _num--;
          if(_num==0) break;
        }
      }
      else{
        _num-=all.len;
        if(all.tot>0) ans1+=all.tot;
        else ans2+=all.tot;
      }
      cnt++;
    }
    printf("+ %.2lf - %.2lf\n",ans1,ans2);
    return true;
  }
};
