//
// Created by hou guoli on 2018/2/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static sqlite3 *db;

int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

sqlite3 *db_connect(char *db_name)
{
    int rc;
    rc = sqlite3_open(db_name, &db);
    return db;
}

int db_exec_stmt(char *sql)
{
    int rc;
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        exit(1);
    }
    return 0;
}

void db_exec()
{
    char *sql = "insert into user (id, name, age) values(?,?,?)";
    sqlite3_stmt *stmt;
    const char *tail;
    int i;
    int ncols;
    int rc;
    char *name="xiaoliang";

    rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "sql error:%s\n", sqlite3_errmsg(db));
    }
    sqlite3_bind_int(stmt, 7, 20);
    sqlite3_bind_text(stmt, 2, name, strlen(name), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, 30);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

}

int main(int argc, char **argv)
{
    char *db_name="test.db";

    db = db_connect(db_name);
// rc = db_exec_stmt(sql);
    db_exec();

    sqlite3_close(db);
    return 0;
}


