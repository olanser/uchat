#include "header.h"

int mx_do_query(char *sql, int (*callback)(void*,int,char**,char**), void* param) {
    sqlite3 *db;
    char *err = 0;
    int a = 5;

    if (sqlite3_open(MX_DATABASE, &db) != SQLITE_OK) {
        fprintf(MX_ERROR_THREAD, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    while (a == 5) {
        a = sqlite3_exec(db, sql, callback, param, &err);
        if (a != 5 && a != SQLITE_OK) {
            fprintf(MX_ERROR_THREAD, "error: database query: %s\n", err);
            sqlite3_free(err);
            sqlite3_close(db);
            return 1;
        }
    }
    // if ((a = sqlite3_exec(db, sql, callback, param, &err)) != SQLITE_OK) {
    //     fprintf(MX_ERROR_THREAD, "error: database query: %s\n", err);
    //     printf("ERRPR SQL NUMBER = %d\n", a);
    //     sqlite3_free(err);
    //     sqlite3_close(db);
    //     return a;
    // }
    sqlite3_close(db);
    return 0;
}
