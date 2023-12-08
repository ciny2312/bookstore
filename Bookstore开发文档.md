#  Bookstore开发文档

> 作者：曹歆茜

## 程序功能概述：

实现一个书店管理系统，维护图书信息，用户信息；并能够记录系统的工作信息。

## 代码文件结构
需求分析文档.md

总体设计文档.md

Bookstore开发文档.md

\code

visitor.h

customer.h

salesman.h

owner.h


\information

info_book.txt

info_user.txt

info_works.txt

## 各个类接口及成员说明

* 游客类：

  1. 账户注册：
    ```
    bool register(string id,string password,string name)
    ```
  2. 账户登录：
    ```
    bool register(string id,string password)
    ```
* 顾客类（继承自游客）：

变量：用户id，密码，用户名，权限
1. 查询图书：
    ```
    bool query(string ISBN)
    bool query(string name)
    bool query(string author)
    bool query(string keyword)
    ```
2. 购买图书：
    ```
    bool buy(string id,int num)
    ```
3. 注销账户：
    ```
    bool logout();
    ```
4. 修改密码：
    ```
    bool change_pass(string id,string cur_pass,string new_pass)
    bool change_pass(string id,string new_pass)
    ```
* 销售人员类（继承自顾客）：

1. 图书进货：
    ```
    bool import(int num,double cost)
    ```
2. 选择图书：
    ```
    void select(string ISBN)
    ```
3. 图书信息修改：
    ```
    bool modify(string ISBN)
    bool modify(string name)
    bool modify(string author)
    bool modify(string* keyword)
    bool modify(double price)
    ```
4.  创建账户：
    ```
    bool useradd(string id,string password,int pr,string name)
    ```

* 店长类（继承自销售）：

1. 财务记录查询：
  ```
  bool ask_finance()
  bool ask_finance(int num)
  ```
2. 生成财务记录报告：
  ```
  void report_finance()
  ```
3. 生成全体员工工作情况报告指令：
  ```
  void report_employee()
  ```
5. 生成日志：
  ```
  void log()
  ```
6. 删除账户：
  ```
  bool delete()
  ```

## 文件存储说明

* 用户数据库：按用户id的字典序记录每个用户的信息，包括：用户id，密码，用户名，账户权限。
* 图书数据库：按ISBN字典序记录每本书的信息，包括：ISBN 号（string）、书名（string）、作者（string）、关键字（string[]）、库存量（int）、单价（double）
* 工作日志：按时间顺序记录系统整体工作
* 员工工作情况表：按时间顺序记录员工工作情况
* 财务报表：按时间顺序记录系统的收入支出

## 其他补充



