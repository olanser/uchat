#include "server.h"

void mx_update_user(t_table_user* tuser, t_server_users *user,
                    t_server *server_info) {
    char sql[300];
    
    sprintf(sql, "select usr_id from user where user.usr_nickname = '%s';",
            tuser->nickname);
    pthread_rwlock_wrlock(&(server_info->m_edit_users));
    mx_do_query(sql, mx_return_one_str, &user->id_users, server_info);
    pthread_rwlock_unlock(&(server_info->m_edit_users));
    printf("user->id = %s\n", user->id_users);
}
