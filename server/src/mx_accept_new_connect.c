#include "server.h"
#include "mxinet.h"

int mx_accept_new_connect(t_server *server_info, int max_connect) {
    int fd;
    int pos = 0;

    if (server_info->size_connekt != max_connect)
        pos = server_info->size_connekt;
    else {
        for (int i = 1; i < server_info->size_connekt; i++) {
            if (server_info->poll_set[i].fd == -1) {
                pos = i;
                break;
            }
        }
    }
    if (pos == 0) {
        fd = accept(server_info->poll_set[0].fd, 0, 0);
        close(fd);
    }
    else {
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        server_info->table_users[pos].socket = accept(
            server_info->poll_set[0].fd, 0, 0);
        if (server_info->table_users[pos].id_users)
            free(server_info->table_users[pos].id_users);
        server_info->table_users[pos].id_users = 0;
        server_info->poll_set[pos].fd =
            server_info->table_users[pos].socket;
        server_info->poll_set[pos].events = POLLIN;
        server_info->poll_set[pos].revents = 0;
        if (pos == server_info->size_connekt)
            server_info->size_connekt++;
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    return -1;
}
