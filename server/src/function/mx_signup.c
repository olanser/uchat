#include "server.h"

static int set_tuser(char *request, t_table_user *tuser) {
    tuser->first_name = &request[9];
    tuser->second_name = &request[60];
    tuser->nickname = &request[111];
    tuser->pass = &request[212];
    return 0;
}

int check_lens(t_table_user *tuser) {
    if (mx_strlen(tuser->first_name) > 50) {
        fprintf(MX_ERROR_THREAD, "Error: first name too long\n");
        return 1;
    }   
    if (mx_strlen(tuser->second_name) > 50) {
        fprintf(MX_ERROR_THREAD, "Error: second name too long\n");
        return 2;
    }
    if (mx_strlen(tuser->nickname) > 100) {
        fprintf(MX_ERROR_THREAD, "Error: nickname too long\n");
        return 3;
    }
    if (mx_strlen(tuser->second_name) > 100) {
        fprintf(MX_ERROR_THREAD, "Error: password too long\n");
        return 4;
    }
    return 0;
}

int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

bool is_nickname_free(char *nickname) {
    sqlite3 *db;
    char *sql = 0;
    char *err = 0;
    int count = 0;

    if (sqlite3_open(MX_DATABASE, &db) != SQLITE_OK) {
        fprintf(MX_ERROR_THREAD, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sql = mx_strjoin("select usr_nickname from user where user.usr_nickname = '", nickname);
    sql = mx_strjoin2(sql, "';");
    if (sqlite3_exec(db, sql, callback, &count, &err) != SQLITE_OK) {
        fprintf(MX_ERROR_THREAD, "error: database query: %s\n", err);
        sqlite3_free(err);
        sqlite3_close(db);
        free(sql);
        return 1;
    }
    if (count != 0) {
       return false;
    }
    free(sql);
    sqlite3_close(db);
    return true;
}

/* 
* 1- false
* 2 - nickname not free
*/
int check_tuser(t_table_user *tuser) {
    if (check_lens(tuser) != 0)
        return MX_QS_ERR_SERV;
    if (mx_check_symbols(tuser)) {
        return MX_QS_ERR_SERV;
    }
    if (!is_nickname_free(tuser->nickname)) {
        return MX_QS_ERR_REG;
    }
    return MX_QS_OK;
}

int change_db(t_user *uset, t_table_user *tuser) {
    char sql[500];

    sprintf(sql, "insert into user values(NULL, '%s', '%s', '%s', '%s', 1);",
        tuser->first_name, tuser->second_name, tuser->nickname, tuser->pass);
    if (mx_do_query(sql, 0, 0) != 0)
        return 1;
    uset->username = mx_strdup(tuser->nickname);
    return 0;
}

static char get_status(t_table_user *tuser, t_user *user) {
    char status = (char)MX_QS_OK;

    status = (char)check_tuser(tuser);
    if (status == MX_QS_ERR_REG) { // nickname busy
    }
    else if (status == MX_QS_ERR_SERV || change_db(user, tuser) != 0) {
        status = MX_QS_ERR_SERV;
    }
    return (char)status;
}

int get_response(char *request, char **response, char status,  t_user *user) {
    if (status != (char)200) {
        *response = malloc(sizeof(char) * 10);
        mx_memcpy(*response,  request, 5);
        memset(&(*response)[5], 0, 4);
        (*response)[5] = 10; // size
        (*response)[9] = status; // status
        return 10;
    }
    *response = malloc(sizeof(char) * 21);
    mx_memcpy(*response,  request, 5);
    memset(&(*response)[5], 0, 16);
    (*response)[5] = 21; // size
    (*response)[9] = status; // status
    strcpy(&(*response)[10], user->id);
    return 21;
}

/*
* length of response
*/
int mx_signup(void *request, char **response, t_user *user) {
    t_table_user *tuser = malloc(sizeof(t_table_user));
    char status = 0;
    int len = 0;

    if (set_tuser(request, tuser) != 0) {
        status = MX_QS_ERR_SERV;
    }
    else {
        status = get_status(tuser, user);
    }
    if (status == (char)MX_QS_OK) {
        mx_update_user(user);
        mx_upd_pr_data(user->id);
    }
    len = get_response(request, response, status, user);
    free(tuser);
    return len;
}
