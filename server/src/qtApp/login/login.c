#include "db.h"
#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pjson.h"

void * userRegister(responseWriter w, request * r)
{}

void * userLogin(responseWriter w, request * r)
{
    char userName[1024];
    char passWord[1024];
    getValueFromBody(r, "userName", userName); 
    getValueFromBody(r, "passWord", passWord); 

    printf("userName: %s\n", userName);
    printf("passWord: %s\n", passWord);

    setValueToBody(&w, "age", (void *)18, INT_MODE);
    setValueToBody(&w, "sex", (void *)"nan", STRING_MODE);

    sendw(w);
}

bool add_user(const char * uname, const char * password)
{
    char *zErrMsg = 0;
    int rc;
    sqlite3 * db; 
    char sql[1024];
    sprintf(sql, "insert into users values('%s', '%s')", uname, password);
    db = db_open();

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }else{
        fprintf(stdout, "Records created successfully\n");
    }

    db_close(db);
    return true;
}

bool allow_login(const char * uname, const char * password)
{
    sqlite3 * db; 
    db = db_open();
    char * perrmsg;
    char ** dbResult;
    int n_row = 0;
    int n_column = 0;
    int ret;
    char real_password[1024];

    char sql[1024];
    sprintf(sql, "select password from users where uname = '%s'", uname);

    ret = sqlite3_get_table(db, sql, &dbResult, &n_row, &n_column, &perrmsg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "exec %s error : %s\n", sql, perrmsg);
        return false;
    }

    strcpy(real_password, dbResult[n_row + n_column - 1]);

    if ((strncmp(password, real_password, strlen(password)) == 0) 
        && (strlen(password) == strlen(real_password)))
    {
        return true;
    }
    else 
    {
        return false;
    }

    db_close(db);
}

void delete_user(const char * uname)
{
    char *zErrMsg = 0;
    int rc;
    sqlite3 * db; 
    char sql[1024];
    sprintf(sql, "delete from users where uname = '%s'", uname);
    db = db_open();

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "delete successfully\n");
    }

    db_close(db);
    return ;
}

#if 0

int main()
{
    //    add_user("李四", "7777");
    //show_table(db_open(), "users");
    //printf("+++++++++++++++++++\n\n");

    /*
    if (allow_login("张三", "3"))
    {
        printf("zhangsan");
    }
    if (allow_login("李四", "7777"));
    {
        printf("lisi\n");
    }
    */

    add_user("pl", "helloworld");
    add_user("pl", "helloworld");
    show_table(db_open(), "users");

    /*
    delete_user("李四");
    printf("___________________\n");
    show_table(db_open(), "users");
    */

    return 0;
}

#endif

