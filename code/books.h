#include <fstream>
#include<iostream>
#include"filework.h"

class books{
  String ISBN,name,author;
  String keys[65];
  int k_num,num,pos;
  double price;
  public:
  books(String _ISBN=String()):ISBN(_ISBN){
    name=String();
    author=String();
    k_num=num=pos=0;
    price=0;
  }
  bool operator<(const books x) const {
    return ISBN<x.ISBN;
  }
  bool operator == (const books x) const {
    return ISBN==x.ISBN;
  }
  bool operator <= (const books x) const {
    return ISBN<=x.ISBN;
  }
  bool enough(int _num){
    return num>=_num;
  }
  bool is_index(String _ISBN){
    return ISBN==_ISBN;
  }
  int get_pos(){
    return pos;
  }
  String get_index(){
    return ISBN;
  }
  void print();
  void add(int _num);
  double sell(int _num);
  void change_isbn(String _name);
  void change_name(String _name);
  void change_author(String _author);
  void change_key(String *_keys,int _num);
  void change_price(double _price);
  void change_pos(int _pos);
  void updata_in_steady(books cur);
};

class books_block{
  public:
  books a[N+50];
  int len,nxt;
};

class books_summary{
  public:
  books fir;
  int nxt,pos;
};

class book_name{
  String index;
  int pos;
  public:
  book_name(String _index=String(),int _pos=0){
    index=_index;pos=_pos;
  }
  bool operator<(const book_name x) const {
    if(index!=x.index) return index<x.index;
    return pos<x.pos;
  }
  bool operator == (const book_name x) const {
    return index==x.index&&pos==x.pos;
  }
  bool is_index(String _index){
    return index==_index;
  }
  int get_pos(){
    return pos;
  }
  String get_index(){
    return index;
  }
};
class book_name_block{
  public:
  book_name a[N+50];
  int len,nxt;
};
class book_name_summary{
  public:
  book_name fir;
  int nxt,pos;
};

class book_author{
  String index;
  int pos;
  public:
  book_author(String _index=String(),int _pos=0){
    index=_index;pos=_pos;
  }
  bool operator<(const book_author x) const {
    if(index!=x.index) return index<x.index;
    return pos<x.pos;
  }
  bool operator == (const book_author x) const {
    return index==x.index&&pos==x.pos;
  }
  bool is_index(String _index){
    return index==_index;
  }
  int get_pos(){
    return pos;
  }
  String get_index(){
    return index;
  }

};
class book_author_block{
  public:
  book_author a[N+50];
  int len,nxt;

};
class book_author_summary{
  public:
  book_author fir;
  int nxt,pos;
};


class book_key{
  String index;
  int pos;
  public:
  book_key(String _index=String(),int _pos=0){
    index=_index;pos=_pos;
  }
  bool operator<(const book_key x) const {
    if(index!=x.index) return index<x.index;
    return pos<x.pos;
  }
  bool operator == (const book_key x) const {
    return index==x.index&&pos==x.pos;
  }
  bool is_index(String _index){
    return index==_index;
  }
  int get_pos(){
    return pos;
  }
  String get_index(){
    return index;
  }
};
class book_key_block{
  public:
  book_key a[N+50];
  int len,nxt;
};
class book_key_summary{
  public:
  book_key fir;
  int nxt,pos;
};


