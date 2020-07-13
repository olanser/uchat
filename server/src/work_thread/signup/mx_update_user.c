#include "server.h"

void mx_update_user(t_table_user* tuser, t_server_users *user,
                    t_server *server_info) {
    char sql[300];
    char *temp = 0;

    sprintf(sql, "select usr_id from user where user.usr_nickname = '%s';",
            tuser->nickname);
    mx_do_query(sql, mx_return_one_str, &temp, server_info);
    pthread_rwlock_wrlock(&(server_info->m_edit_users));
    user->id_users = atoi(temp);
    pthread_rwlock_unlock(&(server_info->m_edit_users));
    free(temp);
    printf("user->id = %d\n", user->id_users);
}
