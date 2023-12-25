#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const int N = 500;
class String {
  int len;
  char s[65];

public:
  String() { len = 0; }
  String(std::string str) {
    len = str.length();
    for (int i = 0; i < len; i++)
      s[i] = str[i];
  }
  String(const String &oth) {
    len = oth.len;
    for (int i = 0; i < len; i++)
      s[i] = oth.s[i];
  }
  std::string into_string() {
    std::string str;
    for (int i = 0; i < len; i++) {
      str = str + s[i];
    }
    return str;
  }
  bool operator<(const String x) const {
    for (int i = 0; i < len; i++) {
      if (s[i] < x.s[i])
        return 1;
      if (s[i] > x.s[i])
        return 0;
    }
    if (len < x.len)
      return 1;
    return 0;
  }
  bool operator>(const String &x) const {
    for (int i = 0; i < len; i++) {
      if (s[i] > x.s[i])
        return 1;
      if (s[i] < x.s[i])
        return 0;
    }
    if (len > x.len)
      return 1;
    return 0;
  }
  bool operator==(const String &x) const {
    if (len != x.len)
      return 0;
    for (int i = 0; i < len; i++) {
      if (s[i] != x.s[i])
        return 0;
    }
    return 1;
  }
  bool operator<=(const String &x) const {
    return *this<x||*this==x;
  }
  bool operator!=(const String &x) const { return !(*this == x); }
};


template <class T, class T_block, class T_summary> class files {
  std::string filename, filesummary;
  std::fstream f_block, f_summary;

public:
  files(std::string _filename) {
    filename = _filename + ".db";
    filesummary = _filename + "_summary.db";
  }

  void updata(T cur){
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    T_summary all, nxt_all;
    T_block b;
    //  debug();
    f_summary.seekg(sizeof(int));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    while (true) {
      if (cur < all.fir)
        break;
      if (all.nxt == 0) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (cur < b.a[i])
            break;
          if (b.a[i]==cur) {
            b.a[i]=cur;
            f_block.seekp(sizeof(T_block) * (all.pos - 1));
            f_block.write(reinterpret_cast<char*>(&b),sizeof(T_block));
            f_block.close();
            f_summary.close();
            return ;
          }
        }
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (all.fir <= cur && cur <= nxt_all.fir) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (cur < b.a[i])
            break;
          if (b.a[i]==cur) {
            b.a[i]=cur;
            f_block.seekp(sizeof(T_block) * (all.pos - 1));
            f_block.write(reinterpret_cast<char*>(&b),sizeof(T_block));
            f_block.close();
            f_summary.close();
            return ;
          }
        }
      }
      all = nxt_all;
    }
    f_block.close();
    f_summary.close();
    return ;
  }
  std::vector<int> show_all(){
    T_block b,nxt_b;std::vector<int>ans;
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    int num;f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char*>(&num),sizeof(int));
    if(num==0){
      f_summary.close();
      f_block.close();
      return ans;
    }
    f_block.seekg(0);
    f_block.read(reinterpret_cast<char*>(&b),sizeof(T_block));
    while(true){
      for (int i = 1; i <= b.len; i++) {
        ans.push_back(b.a[i].get_pos());
      }
      if(b.nxt==0){
        break;
      }
      f_block.seekg(sizeof(T_block) * (b.nxt - 1));
      f_block.read(reinterpret_cast<char *>(&nxt_b), sizeof(T_block));
      b=nxt_b;
    }
    return ans;
  }
  std::vector<int> show(String index){
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    T_summary all, nxt_all;
    T_block b;std::vector<int>ans;
    //  debug();
    int num;f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char*>(&num),sizeof(int));
    if(num==0){
      f_summary.close();
      f_block.close();
      return ans;
    }
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    while (true) {
      if (index < all.fir.get_index())
        break;
      if (all.nxt == 0) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            ans.push_back(b.a[i].get_pos());
          }
        }
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (all.fir.get_index() <= index && index <= nxt_all.fir.get_index()) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            ans.push_back(b.a[i].get_pos());
          }
        }
      }
      all = nxt_all;
    }
    f_block.close();
    f_summary.close();
    return ans;
  }
  T get(String index) {
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    T_summary all, nxt_all;
    T_block b;
    //  debug();
    int num;f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char*>(&num),sizeof(int));
    if(num==0){
      return T();
    }
    f_summary.seekg(sizeof(int));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    while (true) {
      if (index < all.fir.get_index())
        break;
      if (all.nxt == 0) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            return b.a[i];
          }
        }
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (all.fir.get_index() <= index && index <= nxt_all.fir.get_index()) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            return b.a[i];
          }
        }
      }
      all = nxt_all;
    }
    f_block.close();
    f_summary.close();
    return T();
  }

  bool query(String index) {
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    T_summary all, nxt_all;
    T_block b;
    int num, cnt = 0;
    f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char *>(&num), sizeof(int));
    if (num == 0) {
      f_summary.close();
      f_block.close();
      return false;
    }
    //  debug();
    f_summary.seekg(sizeof(int));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    while (true) {
      if (index < all.fir.get_index())
        break;
      if (all.nxt == 0) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            return true;
          }
        }
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (all.fir.get_index() <= index && index <= nxt_all.fir.get_index()) {
        f_block.seekg(sizeof(T_block) * (all.pos - 1));
        f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
        for (int i = 1; i <= b.len; i++) {
          if (index < b.a[i].get_index())
            break;
          if (b.a[i].is_index(index)) {
            f_block.close();
            f_summary.close();
            return true;
          }
        }
      }
      all = nxt_all;
    }
    f_block.close();
    f_summary.close();
    return false;
  }

  void divide(int rk, T_block x) {
    int num;
    f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char *>(&num), sizeof(int));
    num++;
    f_summary.seekp(0);
    f_summary.write(reinterpret_cast<char *>(&num), sizeof(int));
    //  debug();
    T_block y;
    y.len = x.len / 2;
    x.len = x.len - y.len;
    for (int i = x.len + 1; i <= x.len + y.len; i++) {
      y.a[i - x.len] = x.a[i];
    }
    y.nxt = x.nxt;
    x.nxt = num;
    f_block.seekp(sizeof(T_block) * (rk - 1));
    f_block.write(reinterpret_cast<char *>(&x), sizeof(T_block));
    f_block.seekp(0, std::ios::end);
    f_block.write(reinterpret_cast<char *>(&y), sizeof(T_block));
    //  debug();
    T_summary all, nxt_all;
    f_summary.seekg(sizeof(int) + sizeof(T_summary) * (rk - 1));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    nxt_all.fir = y.a[1];
    nxt_all.nxt = all.nxt;
    all.nxt = num;
    nxt_all.pos = num;
    f_summary.seekp(sizeof(int) + sizeof(T_summary) * (rk - 1));
    f_summary.write(reinterpret_cast<char *>(&all), sizeof(T_summary));
    f_summary.seekp(0, std::ios::end);
    f_summary.write(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
    //  debug();
  }
  void merge(int rk, T_block x, T_block y) {
    for (int i = 1; i <= y.len; i++) {
      x.a[i + x.len] = y.a[i];
    }
    x.len += y.len;
    x.nxt = y.nxt;
    f_block.seekp(sizeof(T_block) * (rk - 1));
    f_block.write(reinterpret_cast<char *>(&x), sizeof(T_block));
    T_summary all, nxt_all;
    f_summary.seekg(sizeof(int) + sizeof(T_summary) * (rk - 1));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
    f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
    all.nxt = nxt_all.nxt;
    all.fir = x.a[1];
    f_summary.seekp(sizeof(int) + sizeof(T_summary) * (rk - 1));
    f_summary.write(reinterpret_cast<char *>(&all), sizeof(T_summary));
  }
  void del_in_block(int rk, T cur) {
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.seekg(sizeof(T_block) * (rk - 1));
    T_block b;
    f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
    if (b.a[1]==cur) {
      T_summary all;
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (rk - 1));
      f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
      all.fir = b.a[2];
      f_summary.seekp(sizeof(int) + sizeof(T_summary) * (rk - 1));
      f_summary.write(reinterpret_cast<char *>(&all), sizeof(T_summary));
    }
    for (int i = 1; i <= b.len; i++) {
      if (b.a[i]==cur) {
        for (int j = i; j < b.len; j++) {
          b.a[j] = b.a[j + 1];
        }
        b.len--;
        break;
      }
    }
    if (b.nxt == 0) {
      f_block.seekp(sizeof(T_block) * (rk - 1));
      f_block.write(reinterpret_cast<char *>(&b), sizeof(T_block));
      f_block.close();
      return;
    }
    T_block nxt_b;
    f_block.seekg(sizeof(T_block) * (b.nxt - 1));
    f_block.read(reinterpret_cast<char *>(&nxt_b), sizeof(T_block));
    if (b.len + nxt_b.len <= N) {
      merge(rk, b, nxt_b);
    } else {
      f_block.seekp(sizeof(T_block) * (rk - 1));
      f_block.write(reinterpret_cast<char *>(&b), sizeof(T_block));
    }
    f_block.close();
  }
  void del(T cur) {
    int num;
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char *>(&num), sizeof(int));
    T_summary all, nxt_all;
    f_summary.seekg(sizeof(int));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    
        std::cout<<all.pos<<'\n';
    while (true) {
      if (all.nxt == 0) {
        std::cout<<all.pos<<'\n';
        del_in_block(all.pos, cur);
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (cur < nxt_all.fir) {
        del_in_block(all.pos, cur);
        break;
      }
      all = nxt_all;
    }
    f_summary.close();
  }

  void insert_in_block(int rk, T cur) {
    f_block.open(filename,
                 std::fstream::in | std::fstream::out | std::fstream::binary);
    f_block.seekg(sizeof(T_block) * (rk - 1));
    T_block b;
    f_block.read(reinterpret_cast<char *>(&b), sizeof(T_block));
    if (b.len == 0 || cur < b.a[1]) {
      for (int i = b.len; i >= 1; i--) {
        b.a[i + 1] = b.a[i];
      }
      b.a[1] = cur;
      b.len++;
      T_summary all;
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (rk - 1));
      f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
      all.fir = b.a[1];
      f_summary.seekp(sizeof(int) + sizeof(T_summary) * (rk - 1));
      f_summary.write(reinterpret_cast<char *>(&all), sizeof(T_summary));
    } else {
      for (int i = b.len; i >= 1; i--) {
        if (b.a[i]< cur) {
          for (int j = b.len; j > i; j--) {
            b.a[j + 1] = b.a[j];
          }
          b.a[i + 1] = cur;
          b.len++;
          break;
        }
      }
    }
    if (b.len > N)
      divide(rk, b);
    else {
      f_block.seekp(sizeof(T_block) * (rk - 1));
      f_block.write(reinterpret_cast<char *>(&b), sizeof(T_block));
    }
    f_block.close();
  }
  void insert(T cur) {
    T_summary all, nxt_all;
    f_summary.open(filesummary,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
    int num = 0;
    f_summary.seekg(0);
    f_summary.read(reinterpret_cast<char *>(&num), sizeof(int));
    if (num == 0) {
      num++;
      all.nxt = 0;
      all.pos = 1;
      all.fir = cur;
      f_summary.seekp(0);
      f_summary.write(reinterpret_cast<char *>(&num), sizeof(int));
      f_summary.write(reinterpret_cast<char *>(&all), sizeof(T_summary));
      //  debug();
      f_block.open(filename,
                   std::fstream::in | std::fstream::out | std::fstream::binary);
      T_block b;
      b.nxt = 0;
      b.len = 1;
      b.a[1] = cur;
      f_block.seekp(0);
      f_block.write(reinterpret_cast<char *>(&b), sizeof(T_block));
      f_summary.close();
      f_block.close();
      return;
    }
    f_summary.seekg(sizeof(int));
    f_summary.read(reinterpret_cast<char *>(&all), sizeof(T_summary));
    while (true) {
      if (all.nxt == 0) {
        insert_in_block(all.pos, cur);
        break;
      }
      f_summary.seekg(sizeof(int) + sizeof(T_summary) * (all.nxt - 1));
      f_summary.read(reinterpret_cast<char *>(&nxt_all), sizeof(T_summary));
      if (cur< nxt_all.fir) {
        insert_in_block(all.pos, cur);
        break;
      }
      all = nxt_all;
    }
    f_summary.close();
  }
};