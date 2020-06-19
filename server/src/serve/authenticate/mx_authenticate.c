#include "header.h"

static int read_request(char *request, t_table_user *tuser) {
    tuser->nickname = mx_strdup(&request[9]);
    tuser->pass = mx_strdup(&request[10 + mx_strlen(tuser->nickname)]);
    return 0;
}



static char* get_sql(t_table_user *tuser) {
    char *sql = mx_strdup("select * from user where user.usr_nickname = '");
    sql = mx_strjoin2(sql, tuser->nickname); 
    sql = mx_strjoin2(sql, "' AND user.usr_pass = '");
    sql = mx_strjoin2(sql, tuser->pass);
    sql = mx_strjoin2(sql, "';");
    return  sql;
}

static int callback(void *param, int columns, char** data, char** name) {
    int* count = (int*)((void**)param)[1];
    t_table_user *tuser = (t_table_user*)((void**)param)[0];
    t_user *user = (t_user*)((void**)param)[2];

    *count += 1;
    if (*count == 1) {
        tuser->first_name = mx_strdup(data[1]);
        tuser->second_name = mx_strdup(data[2]);
        tuser->nickname = mx_strdup(data[3]);
        user->id = mx_strdup(data[0]);
        user->username = mx_strdup(data[3]);
    }
    return 0;
}

/* 
return status
*/
static char mx_login_check_user(t_table_user *tuser, t_user *user) {
    char *sql = get_sql(tuser);
    int count = 0;
    void *params[3] = {tuser, &count, user};

    if (user->id != 0)
        return MX_QS_ERR_LOGIN;
    mx_do_query(sql, callback, params);
    if (count == 0)
        return MX_QS_ERR_LOGIN;
    if (count > 1) 
        return MX_QS_ERR_LOG_MANY;
    return (char)MX_QS_OK;
}

static t_table_user* get_tuser() {
    t_table_user *tuser = malloc(sizeof(t_table_user));
    tuser->first_name = 0;
    tuser->second_name = 0;
    tuser->nickname = 0;
    tuser->pass = 0;
    return tuser;
}


/* return len of response */
int mx_authenticate(void *request, char **response, t_user *user_info) {
    t_table_user *tuser = get_tuser();
    char status = 0;
    int len = 0;

    read_request(request, tuser);
    status = mx_login_check_user(tuser, user_info);
    len = mx_get_msg_login(status, request, tuser, response);
    mx_free_tuser(tuser);
    return len;
}