#include "server.h"
#include "defines.h"

static int callback(void *param, int column, char** data, char** name) {
    int* count = (int*)((void**)param)[1];
    t_table_user *tuser = (t_table_user*)((void**)param)[0];
    t_server_users *user = (t_server_users *)((void**)param)[2];

    *count += 1;
    if (*count == 1) {
        tuser->first_name = mx_strdup(data[1]);
        tuser->second_name = mx_strdup(data[2]);
        user->id_users = atoi(data[0]);
        tuser->id = user->id_users;
        tuser->avatar = data[6][0];
    }
    return 0;
}

char mx_login_check_user(t_table_user *tuser, t_server *server_info,
                                t_server_users *user) {
    char sql[300];
    int count = 0;
    void *params[3] = {tuser, &count, user};

    sprintf(sql, "select * from user where user.usr_nickname = '%s' AND "
        "user.usr_pass = '%s';", tuser->nickname, tuser->pass);
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