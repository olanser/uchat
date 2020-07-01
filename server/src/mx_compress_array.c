#include "server.h"

void mx_compress_array(t_server *server_info) {
    t_server_users *temp;
    bool check = true;

    // for (int i = 1; i < server_info->size_connekt; i++)
    //     printf("%d ", server_info->poll_set[i].fd);
    // printf("\n");
    if (mx_check_not_work(&(server_info->table_users[server_info->size_connekt - 1]))) {
        mx_add_log(server_info, "START compress_array\n");
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        for (int i = 1; i < server_info->size_connekt && check; i++) {
            if (server_info->poll_set[i].fd == -1) {
                server_info->poll_set[i].fd = server_info->poll_set[server_info->size_connekt - 1].fd;
                server_info->table_users[i] = server_info->table_users[server_info->size_connekt - 1];
                server_info->table_users[server_info->size_connekt - 1].id_users = 0;
                server_info->size_connekt -= 1;
                server_info->poll_set[i].events = POLLIN;
                server_info->poll_set[i].revents = 0;
                i--;
                check = mx_check_not_work(&(server_info->table_users[server_info->size_connekt - 1]));
            }
        }
        mx_add_log(server_info, "END compress_array\n");
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    // for (int i = 1; i < server_info->size_connekt; i++)
    // printf("%d ", server_info->poll_set[i].fd);
    // printf("\n");
    server_info->compress_array = false;
}
