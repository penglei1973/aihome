#include "db.h"
#include "aihome.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool InitializeDatabase()
{
    char *zErrMsg = 0;
    int rc;
    sqlite3 * db; 
    char * sql = "CREATE TABLE USERS(UNAME TEXT INTPRIMARY KEY NOT NULL, PASSWORD TEXT)";
    db = db_open();

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        //fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        db_close(db);
        return false;
    }

    db_close(db);
    return true;
}

sqlite3 * db_open()
{
    sqlite3 * db;
    char * zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_PATH, &db);

    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }

    return db;
}

void db_close(sqlite3 * db)
{
    sqlite3_close(db);
}

int show_table(sqlite3 * pdb, const char * table_name)
{
    char * perrmsg;
    char ** dbResult;
    int n_row = 0;
    int n_column = 0;
    int i = 0, j = 0, index = 0;
    int ret;

    char sql[1024] = "select * from ";
    strcat(sql, table_name);

    ret = sqlite3_get_table(pdb, sql, &dbResult, &n_row, &n_column, &perrmsg);
    if (ret != SQLITE_OK)
    {
        fprintf(stderr, "exec %s error : %s\n", sql, perrmsg);
        db_close(pdb);
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < n_column; j++)
    {
        printf("%s\t", dbResult[j]);
    }

    putchar('\n');
    index = n_column;

    for (i = 0; i < n_row; i++)
    {
        for (j = 0; j < n_column; j++)
        {
            printf("%s\t", dbResult[index]);
            index++;
        }

        putchar('\n');
    }

    db_close(pdb);

    return 0;
}
