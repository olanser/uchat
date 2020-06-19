#include "header.h"
#include "mxinet.h"

int mx_accept_new_connect(t_server *server_info, int max_connect) {
    int fd;

    if (server_info->size_connekt != max_connect) {
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        server_info->table_users[server_info->size_connekt].socket = accept(
            server_info->poll_set[0].fd, 0, 0);
        server_info->table_users[server_info->size_connekt].id_users = 0;
        server_info->poll_set[server_info->size_connekt].fd =
            server_info->table_users[server_info->size_connekt].socket;
        server_info->poll_set[server_info->size_connekt].events = POLLIN;
        server_info->poll_set[server_info->size_connekt].revents = 0;
        server_info->size_connekt++;
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    else {
        fd = accept(server_info->poll_set[0].fd, 0, 0);
        close(fd);
    }
    return -1;
}