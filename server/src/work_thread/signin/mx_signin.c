#include "server.h"
#include "defines.h"

static int read_request(char *request, t_table_user *tuser) {
    tuser->nickname = mx_strdup(&request[9]);
    tuser->pass = mx_strdup(&request[110]);
    return 0;
}

static int callback(void *param, int columns, char** data, char** name) {
    int* count = (int*)((void**)param)[1];
    t_table_user *tuser = (t_table_user*)((void**)param)[0];
    t_server_users *user = (t_server_users *)((void**)param)[2];

    *count += 1;
    if (*count == 1) {
        tuser->first_name = mx_strdup(data[1]);
        tuser->second_name = mx_strdup(data[2]);
        user->id_users = mx_strdup(data[0]);
        tuser->id = user->id_users;
    }
    return 0;
}

static char mx_login_check_user(t_table_user *tuser, t_server *server_info, t_server_users *user) {
    char sql[300];
    int count = 0;
    void *params[3] = {tuser, &count, user};

    sprintf(sql, "select * from user where user.usr_nickname = '%s' AND user.usr_pass = '%s';",
        tuser->nickname, tuser->pass);
    if (user->id_users != 0)
        return MX_QS_ERR_LOGIN;
    pthread_rwlock_wrlock(&(server_info->m_edit_users));
    mx_do_query(sql, callback, params, server_info);
    pthread_rwlock_unlock(&(server_info->m_edit_users));
    if (count == 0)
        return MX_QS_ERR_LOGIN;
    if (count > 1) 
        return MX_QS_ERR_LOG_MANY;
    return (char)MX_QS_OK;
}

static void mx_free_tuser(t_table_user *tuser) {
    free(tuser->first_name);
    free(tuser->second_name);
    free(tuser->nickname);
    free(tuser->pass);
}

static t_table_user* get_tuser() {
    t_table_user *tuser = malloc(sizeof(t_table_user));
    tuser->first_name = 0;
    tuser->second_name = 0;
    tuser->nickname = 0;
    tuser->pass = 0;
    tuser->id = 0;
    return tuser;
}

char *mx_signin(t_server *server_info, t_server_users *user) {
    t_table_user *tuser = get_tuser();
    char status = 0;
    int len = 0;
    char *response = 0;

    read_request(user->buff, tuser);
    status = mx_login_check_user(tuser, server_info, user);
    mx_get_msg_login(status, user->buff, tuser, &response);
    printf("tuser->nickname: %s\n", tuser->nickname);
    printf("tuser->pass: %s\n", tuser->pass);
    printf("status: %d\n", status);
    mx_free_tuser(tuser);
    free(tuser);
    return response;
}
