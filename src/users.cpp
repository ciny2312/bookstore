#include "users.h"
#include <algorithm>
#include <fstream>
#include <vector>

bool users::register_user(String _id, String _password, String _name) {
  files<users,users_block, users_summary> f("../information/info_users");
  if (f.query(_id))
    return false;
  users nw(_id, _password, _name, 1);
  f.insert(nw);
  return true;
}
bool users::su(String _id) {
  files<users,users_block, users_summary> f("../information/info_users");
  if (!f.query(_id))
    return false;
  users nw = f.get(_id);
  if (nw.pri >= pri)
    return false;
  *this = nw;
  return true;
}
bool users::su(String _id, String _password) {
  files<users,users_block, users_summary> f("../information/info_users");
  if (!f.query(_id))
    return false;
  users nw = f.get(_id);
  if (nw.password != _password)
    return false;
  *this = nw;
  return true;
}

bool users::show(int ty, String index) {
  if (pri < 1)
    return false;
  std::vector<int> ans;
  if (ty == 0) {
    files<books,books_block,books_summary> f("../information/info_books");
    ans=f.show_all();
  } else if (ty == 1) {
    files<books,books_block,books_summary> f("../information/info_books");
    ans=f.show(index);
  } else if (ty == 2) {
    files<book_name,book_name_block,book_name_summary> f("../information/book_name");
    ans=f.show(index);
  } else if (ty == 3) {
    files<book_author,book_author_block,book_author_summary> f("../information/book_author");
    ans=f.show(index);
  } else {
    files<book_key,book_key_block,book_key_summary> f("../information/book_key");
    ans=f.show(index);
  }
  int num=ans.size();
  if(num==0){
    printf("\n");
    return true;
  }
  books _ans[N*N];
  std::fstream f_steady;
  f_steady.open("../information/info_steady.db",std::fstream::in | std::fstream::out | std::fstream::binary);
  for(int i=0;i<num;i++){
    f_steady.seekg(sizeof(int)+sizeof(books)*(ans[i]-1));
    f_steady.read(reinterpret_cast<char*>(&_ans[i]),sizeof(books));
  }
  std::sort(_ans,_ans+num);
  for(int i=0;i<num;i++){
    _ans[i].print();
  }
  f_steady.close();
  return true;
}
bool users::buy(String _isbn, int num) {
  files<books,books_block, books_summary> f("../information/info_books");
  if (pri < 1)
    return false;
  if (!f.query(_isbn))
    return false;
  if (num <= 0)
    return false;
  books cur = f.get(_isbn);
  if(!cur.enough(num)) return false;
  double cost = cur.sell(num);
  finance f_money;
  f_money.insert(cost);
  printf("%lf\n", cost);
  return true;
}
bool users::logout() {
  if(pri<1) return false;

  return true;
}
bool users::change_pass(String _id, String cur_pass, String new_pass) {
  files<users,users_block, users_summary> f("../information/info_users");
  if (pri < 1)
    return 0;
  if (!f.query(_id))
    return false;
  users cur=f.get(_id);
  if (cur.password != cur_pass)
    return false;
  cur.password = new_pass;
  f.updata(cur);
  return true;
}
bool users::change_pass(String _id, String new_pass) {
  files<users,users_block,users_summary> f("../information/info_users");
  if (pri != 7)
    return false;
  if (!f.query(_id))
    return false;
  users cur=f.get(_id);
  cur.password = new_pass;
  f.updata(cur);
  return true;
}
bool users::useradd(String _id, String _password, int _pri, String _name) {
  files<users,users_block,users_summary> f("../information/info_users");
  if (pri < 3)
    return false;
  if (_pri >= pri)
    return false;
  if (f.query(_id))
    return false;
  users nw(_id, _password, _name, _pri);
  f.insert(nw);
  return true;
}
bool users::select(String ISBN, int &book_pos) {
  files<books,books_block,books_summary> f("../information/info_books");
  if (pri < 3)
    return false;
  if (!f.query(ISBN)) {
    books nw(ISBN);
    std::fstream f_steady;
    f_steady.open("../information/info_steady.db",std::fstream::in | std::fstream::in | std::fstream::binary);
    int num;
    f_steady.seekg(0);
    f_steady.read(reinterpret_cast<char*>(&num),sizeof(int));
    nw.change_pos(++num);
    book_pos=num;
    f_steady.seekp(0);
    f_steady.write(reinterpret_cast<char*>(&num),sizeof(int));
    f_steady.seekp(std::ios::end);
    f_steady.write(reinterpret_cast<char*>(&nw),sizeof(books));
    f.insert(nw);
  }
  books cur=f.get(ISBN);
  book_pos = cur.get_pos();
  return true;
}
bool users::have_pri(int p) { return pri >= p; }
bool users::modify(int ty, String index, books b) {
  //  std::cout<<"HERE1"<<'\n';
  if (ty == 0) {
    if (b.is_index(index))
      return false;
  //  std::cout<<"HERE2"<<'\n';
    b.change_isbn(index);
  } else if (ty == 1) {
    b.change_name(index);
  } else {
    b.change_author(index);
  }
  return true;
}
bool users::modify(String *keys, int num, books b) {
  b.change_key(keys, num);
  return true;
}
bool users::modify(double price, books b) {
  b.change_price(price);
  return true;
}
bool users::import(int num, double cost, books b) {
  if (pri < 3)
    return false;
  if (num <= 0)
    return false;
  if (cost <= 0)
    return false;
  b.add(num);
  finance f_money;
  f_money.insert(-cost);
  return true;
}
bool users::del(String _id) {
  if (pri < 7)
    return false;
  files<users,users_block, users_summary> f("../information/info_users");
  if (!f.query(_id))
    return false;
  //  if(f_log.ask(_id)) return false;
  f.del(_id);
  return true;
}
bool users::show_finance(int num) {
  if (pri < 7)
    return false;
  finance f_money;
  if(!f_money.show(num)) return false;
  return true;
}
bool users::report_finance() {
  if (pri < 7)
    return false;
  printf("The list is in finance.db");
  return true;
}
bool users::report_employee() {
  if (pri < 7)
    return false;
  printf("The list is in workers.db");
  return true;
}
bool users::log() {
  if (pri < 7)
    return false;
  printf("The list is in tot_work.db");
  return true;
}