#include "books.h"
#include <fstream>

void books::print(){
  std::cout<<ISBN.into_string();
  printf("\t");
  std::cout<<name.into_string();
  printf("\t");
  std::cout<<author.into_string();
  printf("\t");
  for(int i=1;i<=k_num;i++){
    std::cout<<keys[i].into_string();
    if(i!=num) printf("|");
  }
  printf("\t");
  printf("%lf\t",price);
  printf("%d\n",num);
}
void books::updata_in_steady(books cur){
  std::fstream f_steady;
  f_steady.open("information/info_steady.db",std::fstream::in | std::fstream::out | std::fstream::binary);
  f_steady.seekp(sizeof(int)+sizeof(books)*(cur.pos-1));
  f_steady.write(reinterpret_cast<char*>(&cur),sizeof(books));
  f_steady.close();
}
void books::add(int _num) {
  num += _num;
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
  return;
}
double books::sell(int _num) {
  num -= _num;
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
  return price * _num;
}
void books::change_isbn(String _isbn) {
  files<books,books_block,books_summary>f("information/info_books");
  f.del(*this);
  ISBN = _isbn;
  f.insert(*this);
  updata_in_steady(*this);
}
void books::change_name(String _name) {
  files<book_name,book_name_block,book_name_summary>f_name("information/book_name");
  if(name!=String()){
    book_name cur(name,pos);
    f_name.del(cur);
  }
  name = _name;
  book_name cur(name,pos);
  f_name.insert(cur);
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
}
void books::change_author(String _author) {
  files<book_author,book_author_block,book_author_summary>f_name("information/book_author");
  if(author!=String()){
    book_author cur(author,pos);
    f_name.del(cur);
  }
  author = _author;
  book_author cur(author,pos);
  f_name.insert(cur);
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
}
void books::change_key(String *_keys, int _num) {
  for (int i = 1; i <= k_num; i++) {
    files<book_key, book_key_block, book_key_summary> f_name("information/book_key");
    book_key cur(keys[i],pos);
    f_name.del(cur);
  }
  k_num = _num;
  for (int i = 1; i <= k_num; i++) {
    files<book_key, book_key_block, book_key_summary> f_name("information/book_key");
    keys[i]=_keys[i];
    book_key cur(keys[i],pos);
    f_name.insert(cur);
  }
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
}
void books::change_price(double _price) {
  price = _price;
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
}
void books::change_pos(int _pos) {
  pos=_pos;
  files<books,books_block,books_summary>f("information/info_books");
  f.updata(*this);
  updata_in_steady(*this);
}