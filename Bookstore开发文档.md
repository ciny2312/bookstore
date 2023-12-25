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

$\qquad$ books.h

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

* 游客类：

  1. 账户注册：
    ```
    bool register(String id,String password,String name)
    ```
  2. 账户登录：
    ```
    bool su(String id)
    bool su(String id,String password)
    ```
* 顾客类（继承自游客）：

变量：用户id，密码，用户名，权限
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
* 销售人员类（继承自顾客）：

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

* 店长类（继承自销售）：

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

## 文件存储说明
* 用户数据库：
按用户id的字典序记录每个用户的信息，包括：用户id，密码，用户名，账户权限。
* 图书数据库：
按ISBN字典序记录每本书的信息，包括：ISBN 号（string）、书名（string）、作者（string）、关键字（string[]）、库存量（int）、单价（double）
* 书名表：
按书名的字典序排列，记录该书在图书数据库中的位置
* 作者表：
按书名的字典序排列，记录拥有该作者的所有图书在图书数据库中的位置
* 书名表：
按书名的字典序排列，记录拥有该书名的所有图书在图书数据库中的位置
* 关键字表
按关键字的字典序排列，记录拥有该关键字的所有图书在图书数据库中的位置
* 工作日志：
按时间顺序记录系统整体工作
* 员工工作情况表：
按时间顺序记录员工工作情况
* 财务报表：
按时间顺序记录系统的收入支出
* 数据库大小
记录三个非负整数：用户数量，图书数量，交易数量
## 其他补充



