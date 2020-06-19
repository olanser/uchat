#include "header.h"
#include "mxinet.h"

int mx_accept_new_connect(t_server *server_info, int max_connect) {
    int fd;

    if (server_info->size_connekt != max_connect) {
        server_info->table_users[server_info->size_connekt].socket = accept(
            server_info->poll_set[0].fd, 0, 0);
        server_info->poll_set[server_info->size_connekt].fd =
            server_info->table_users[server_info->size_connekt].socket;
        server_info->size_connekt++;
        return -1;
    }
    else {
        fd = accept(server_info->poll_set[0].fd, 0, 0);
        close(fd);
    }
    return -1;
}