#include "header.h"

void mx_compress_array(t_server *server_info) {
    t_server_users *temp;

    for (int i = 1; i < server_info->size_connekt; i++)
        printf("%d ", server_info->poll_set[i].fd);
    printf("\n\n\n");
    
    pthread_rwlock_wrlock(&(server_info->m_edit_users));
    for (int i = 1; i < server_info->size_connekt; i++) {
        if (server_info->poll_set[i].fd == -1) {
            if (mx_check_not_work(server_info->table_users[server_info->size_connekt - 1])) {
                server_info->poll_set[i].fd = server_info->poll_set[server_info->size_connekt - 1].fd;
                server_info->table_users[i] = server_info->table_users[server_info->size_connekt - 1];
                server_info->size_connekt -= 1;
                server_info->poll_set[i].events = POLLIN;
                server_info->poll_set[i].revents = 0;
                i--;
            }
            else {
                server_info->poll_set[i].events = 0;
            }
        }
    }
    pthread_rwlock_unlock(&(server_info->m_edit_users));
    for (int i = 1; i < server_info->size_connekt; i++)
    printf("%d ", server_info->poll_set[i].fd);
    printf("\n");
    server_info->compress_array = false;
}
