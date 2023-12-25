#  Bookstore开发文档

> 作者：曹歆茜

## 程序功能概述：

实现一个书店管理系统，维护图书信息，用户信息；并能够记录系统的工作信息。

## 代码文件结构
需求分析文档.md

总体设计文档.md

Bookstore开发文档.md


/code

$\qquad$/prework

$\qquad\qquad$ 2074.cpp

$\qquad$ users.h

$\qquad$ users.cpp

$\qquad$ books.h

$\qquad$ books.cpp

$\qquad$ filework.h

$\qquad$ main.cpp



/information

$\qquad$ info_steady.db

$\qquad$ info_books.db

$\qquad$ info_books_summary.db

$\qquad$ info_users.db

$\qquad$ info_users_summary.db

$\qquad$ info_finance.db

$\qquad$ info_finance_summary.db

$\qquad$ book_name.db

$\qquad$ books_name_summary.db

$\qquad$ book_author.db

$\qquad$ books_author_summary.db

$\qquad$ book_key.db

$\qquad$ books_key_summary.db

$\qquad$ tot_work.db

$\qquad$ finance.db

$\qquad$ workers.db


## 各个类接口及成员说明

* 用户类：
变量：用户id，密码，用户名，权限
> 游客
  1. 账户注册：
    ```
    bool register(String id,String password,String name)
    ```
  2. 账户登录：
    ```
    bool su(String id)
    bool su(String id,String password)
    ```
> 顾客：

1. 查询图书：
    ```
    bool show(int ty,String index)
    ty==0 all
    ty==1 ISBN
    ty==2 name
    ty==3 author
    ty==4 keys
    ```
2. 购买图书：
    ```
    bool buy(String id,int num)
    ```
3. 注销账户：
    ```
    bool logout();
    ```
4. 修改密码：
    ```
    bool change_pass(String id,String cur_pass,String new_pass)
    bool change_pass(String id,String new_pass)
    ```
> 销售人员：

1.  创建账户：
    ```
    bool useradd(String id,String password,int pr,String name)
    ```
2. 选择图书：
    ```
    bool select(String ISBN)
    ```
3. 图书信息修改：
    ```
    bool modify(int ty,String index,books b)
    ty==0  ISBN
    ty==1  name
    ty==2  author

    bool modify(String* keyword,books b)
    bool modify(double price,books b)
    ```
4. 图书进货：
    ```
    bool import(int num,double cost)
    ```

> 店长：

1. 财务记录查询：
  ```
  bool show_finance(int num)
  ```
2. 生成财务记录报告：
  ```
  bool report_finance()
  ```
3. 生成全体员工工作情况报告指令：
  ```
  bool report_employee()
  ```
5. 生成日志：
  ```
  bool log()
  ```
6. 删除账户：
  ```
  bool delete()
  ```
* 图书类
```
class books{
  String ISBN,name,author;
  String keys[65];
  int k_num,num,pos;
  double price;
  
  public:
  books(String _ISBN=String()):ISBN(_ISBN);
  bool operator<(const books x) const ;
  bool operator == (const books x) ;
  bool operator <= (const books x) const;
  bool enough(int _num);
  bool is_index(String _ISBN);
  int get_pos();
  String get_index();
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
}
```
* 文件读写类
```

template <class T, class T_block, class T_summary>
class files {
  std::string filename, filesummary;
  std::fstream f_block, f_summary;

public:
  files(std::string _filename) {
    filename = _filename + ".db";
    filesummary = _filename + "_summary.db";
  }

  void updata(T cur);
  std::vector<int> show_all();
  std::vector<int> show(String index);
  T get(String index) ;
  bool query(String index);
  void divide(int rk, T_block x) ;
  void merge(int rk, T_block x, T_block y);
  void del_in_block(int rk, T cur) ;
  void del(T cur);
  void insert_in_block(int rk, T cur);
  void insert(T cur);
};
```
* 书名（及其块状链表）类

* 作者（及其块状链表）类

* 关键字（及其块状链表）类

* 财务（及其块状链表）类


## 文件存储说明
* 用户数据库：
按用户id的字典序记录每个用户的信息，包括：用户id，密码，用户名，账户权限。
* 图书数据库：
按ISBN字典序记录每本书的信息，包括：ISBN 号（string）、书名（string）、作者（string）、关键字（string[]）、库存量（int）、单价（double）
* 图书总表
* 书名表：
按书名的字典序排列，记录该书在图书总表中的位置
* 作者表：
按书名的字典序排列，记录拥有该作者的所有图书在图书总表中的位置
* 书名表：
按书名的字典序排列，记录拥有该书名的所有图书在图书总表中的位置
* 关键字表
按关键字的字典序排列，记录拥有该关键字的所有图书在图书总表中的位置
* 工作日志：
按时间顺序记录系统整体工作
* 员工工作情况表：
按时间顺序记录员工工作情况
* 财务报表：
按时间顺序记录系统的收入支出
## 其他补充



