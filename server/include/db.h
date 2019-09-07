#ifndef __DB_H_
#define __DB_H_
#include <sqlite3.h>

extern sqlite3 * db_open();
extern void db_close(sqlite3 * db);
extern int show_table(sqlite3 * pdb, const char * table_name);

#endif
