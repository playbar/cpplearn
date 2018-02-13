//
// Created by hou guoli on 2018/2/13.
//

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

/***************************
typedef int (*sqlite3_callback)(
void*,    // Data provided in the 4th argument of sqlite3_exec()
int,        // The number of columns in row
char**,   // An array of strings representing fields in the row
char**    // An array of strings representing column names
);

***************************/

/* callback函数只有在对数据库进行select, 操作时才会调用 */
static int select_callback(void *data, int argc, char **argv, char **azColName){
    int i;
    printf("%s", (char*)data);
    for(i=0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
    static sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* 数据库创建或打开 */
    rc = sqlite3_open("testaa.db", &db);

    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }

    const char* sql = "create table healthinfo (sid int primary key not null, name text not null, ishealth char(4) not null);";

    /* 创建表 */
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

    sql = "insert into healthinfo (sid, name, ishealth)" \
           "values (201601001, 'xiaowang', 'yes');" \
           "insert into healthinfo (sid, name, ishealth)" \
           "values (201601002, 'xiaoli', 'yes');" \
           "insert into healthinfo (sid, name, ishealth)" \
           "values (201601003, 'xiaozhang', 'no');" \
           "insert into healthinfo (sid, name, ishealth)" \
           "values (201601004, 'xiaozhou', 'yes');" \
           "insert into healthinfo (sid, name, ishealth)" \
           "values (201601005, 'xiaosun', 'yes');";

    /* 插入数据 */
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table insert data successfully\n");
    }

    char* strname = "xiaoyang";
    //char strname[256] = {'x','i','a','o','y','a','n','g'};
    char sql2[256] = {'0'};
    /* 不推荐使用这种方式 */
    sprintf(sql2, "insert into healthinfo (sid, name, ishealth) values (201601006, '%s', 'yes');", strname);
    /* 插入数据 */
    rc = sqlite3_exec(db, sql2, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table insert data successfully\n");
    }

    /***********  存数据和取数据的第二种方法***********/

    sql = "insert into healthinfo (sid, name, ishealth)" \
           "values (:sid, :name, :ishealth);";   /* 注: ":sid" 为命名参数 也可以用? 号*/

    sqlite3_stmt *stmt;
    /* 准备一个语句对象 */
    sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    /* 语句对象绑定的参数个数也就是上面sql语句values括号中的参数 */
    printf("max_parameter_count = %d\n", sqlite3_bind_parameter_count(stmt));
    /* 只有上面指定了:sid这个名字才可以用 */
    printf("sid parameter index = %d\n", sqlite3_bind_parameter_index(stmt, ":sid"));
    printf("name parameter index = %d\n", sqlite3_bind_parameter_index(stmt, ":name"));
    printf("ishealth parameter index = %d\n", sqlite3_bind_parameter_index(stmt, ":ishealth"));
    /* 如果是?号命名的则返回的文本为null */
    printf("index = 1 's parameter's name = %s\n", sqlite3_bind_parameter_name(stmt, 1));
    sqlite3_bind_int(stmt, 1, 201601007);
    sqlite3_bind_text(stmt, 2, "xiaoqian", -1, NULL); /* 第四个参数设为负数则自动计算第三个参数的长度 */
    sqlite3_bind_text(stmt, 3, "yes", 3, NULL);
    //sqlite3_bind_blob(stmt, 1, sectionData, 4096, SQLITE_STATIC); /* 将sectonData 绑定到stmt对象 */

    /* 执行sql 语句对象并判断其返回值
        发现如果不是select 这样会产生结果集的操作
        返回值为SQLITE_DONE 或者出错，只有执行sql语句会产生
        结果集执行step函数才返回SQLITE_ROW*/
    rc = sqlite3_step(stmt);
    printf("step() return %s\n", rc == SQLITE_DONE ? "SQLITE_DONE" \
                                          : rc == SQLITE_ROW ? "SQLITE_ROW" : "SQLITE_ERROR");

    sqlite3_reset(stmt);  /* 如果要重新绑定其他值要reset一下 */
    sqlite3_bind_int(stmt, 1, 201601008);
    sqlite3_bind_text(stmt, 2, "xiaowu", -1, NULL); /* 重新绑定值 */
    sqlite3_bind_text(stmt, 3, "yes", 3, NULL);
    sqlite3_step(stmt);  /* 再执行 */

    /* 销毁prepare 创建的语句对象 */
    sqlite3_finalize(stmt);

    /* 取数据 */
    //sql = "select * from healthinfo;";
    sql = "select * from healthinfo limit 4 offset 2;";  /* 限制返回4行且从第3行开始 */
    sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    printf("total_column = %d\n", sqlite3_column_count(stmt));

    /* 遍历执行sql语句后的结果集的每一行数据 */
    while(sqlite3_step(stmt) == SQLITE_ROW){
        /* 获得字节数，第二个参数为select结果集合的列号 */
        /* 由于select 的结果集只有section这一列，因此为0 */
        int len_sid = sqlite3_column_bytes(stmt, 0);
        int len_name = sqlite3_column_bytes(stmt, 1);
        int len_ishealth = sqlite3_column_bytes(stmt, 2);

        printf("sid = %d, len = %d\n", sqlite3_column_int(stmt, 0), len_sid);
        printf("name = %s, len = %d\n", sqlite3_column_text(stmt, 1), len_name);
        printf("ishealth = %s, len = %d\n", sqlite3_column_text(stmt, 2), len_ishealth);
        //unsigned char* srcdata = sqlite3_column_blob(stmt, 0);  /* 取得数据库中的blob数据 */
    }
    printf("\n");
    sqlite3_finalize(stmt);
    /******************* end ****************************/


    const char* data = "select call back function call!\n";
    /* select 使用*/
    sql = "select * from healthinfo where ishealth == 'yes';";
    rc = sqlite3_exec(db, sql, select_callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table select successfully\n");
    }

    data = "update call back function call!\n";
    /* update 使用*/
    sql = "update healthinfo set ishealth = 'no' where name='xiaoli';" \
            "select * from healthinfo where ishealth == 'yes';";
    rc = sqlite3_exec(db, sql, select_callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table update successfully\n");
    }


    /* 删除表 */
    sql = "drop table healthinfo;";
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table droped successfully\n");
    }


    char sql5[256];
    char* tname = "abc";
    sprintf(sql5, "create table if not exists %s ("\
                    "id int not null," \
                    "name text not null);", tname);

    printf("%s\n", sql5);

    /* 创建表 */
    rc = sqlite3_exec(db, sql5, NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_close(db);
}




