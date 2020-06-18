#include "header.h"

static int callback (void *data, int argc, char **rows, char **names) {
    int i = 0;
    *(char**)data = mx_strdup(rows[0]);

    return 0;
}

void mx_update_user(t_user* user) {
    sqlite3 *db;
    char *sql = 0;
    char *err = 0;
    
    sql = mx_strjoin("select usr_id from user where user.usr_nickname = '", user->username);
    sql = mx_strjoin2(sql, "';");
    
    mx_do_query(sql, &callback, &user->id);
    printf("user->id = %s\n", user->id);
    free(sql);
}