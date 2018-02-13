//
// Created by hou guoli on 2018/2/13.
//

/*
@brief 本程序测试sqlite数据库的增删改查
@date 2012-09-03
*/
// SQLiteTest.cpp : Defines the entry point for the console application.
//

#include "sqlite3.h"
#include <iostream>
using namespace std;

sqlite3 * pDB = NULL;

//增加用户
bool AddUser(const string& sName, const string& sAge);
//删除用户
bool DeleteUser(const string& sName);
//修改用户
bool ModifyUser(const string& sName, const string& sAge);
//查找用户
bool SelectUser();

int main(int argc, char* argv[])
{
    //打开路径采用utf-8编码
    //如果路径中包含中文，需要进行编码转换
    int nRes = sqlite3_open("./test.db", &pDB);
    if (nRes != SQLITE_OK)
    {
        cout<<"Open database fail: "<<sqlite3_errmsg(pDB);
        goto QUIT;
    }

    //添加“赵钱孙李”
    if (    !AddUser("zhao", "18")
            || !AddUser("qian", "19")
            || !AddUser("sun", "20")
            || !AddUser("li", "21"))
    {
        goto QUIT;
    }

    //删除“赵”
    if (!DeleteUser("zhao"))
    {
        goto QUIT;
    }

    //修改“孙”
    if (!ModifyUser("sun", "15"))
    {
        goto QUIT;
    }

    //查找用户
    if (!SelectUser())
    {
        goto QUIT;
    }

    QUIT:
    sqlite3_close(pDB);

    return 0;
}

bool AddUser(const string& sName, const string& sAge)
{
    string strSql = "";
    strSql += "insert into user(name,age)";
    strSql += "values('";
    strSql += sName;
    strSql += "',";
    strSql += sAge;
    strSql += ");";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        cout<<"add user fail: "<<cErrMsg<<endl;
        return false;
    }
    else
    {
        cout<<"add user success: "<<sName.c_str()<<"\t"<<sAge.c_str()<<endl;
    }

    return true;
}

bool DeleteUser(const string& sName)
{
    string strSql = "";
    strSql += "delete from user where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        cout<<"delete user fail: "<<cErrMsg<<endl;
        return false;
    }
    else
    {
        cout<<"delete user success: "<<sName.c_str()<<endl;
    }

    return true;
}

bool ModifyUser(const string& sName, const string& sAge)
{
    string strSql = "";
    strSql += "update user set age =";
    strSql += sAge;
    strSql += " where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        cout<<"modify user fail: "<<cErrMsg<<endl;
        return false;
    }
    else
    {
        cout<<"modify user success: "<<sName.c_str()<<"\t"<<sAge.c_str()<<endl;
    }

    return true;
}

static int UserResult(void *NotUsed, int argc, char **argv, char **azColName)
{
    for(int i = 0 ; i < argc ; i++)
    {
        cout<<azColName[i]<<" = "<<(argv[i] ? argv[i] : "NULL")<<", ";
    }
    cout<<endl;

    return 0;
}

bool SelectUser()
{
    char* cErrMsg;
    int res = sqlite3_exec(pDB, "select * from user;", UserResult , 0 , &cErrMsg);

    if (res != SQLITE_OK)
    {
        cout<<"select fail: "<<cErrMsg<<endl;
        return false;
    }

    return true;
}