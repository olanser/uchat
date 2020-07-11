#include "server.h"
#include "mxinet.h"

static int check_pos(t_server *server_info, int max_connect) {
    if (server_info->size_connekt != max_connect)
        return server_info->size_connekt;
    else {
        for (int i = 1; i < server_info->size_connekt; i++) {
            if (server_info->poll_set[i].fd == -1) {
                return i;
            }
        }
    }
    return 0;
}

static bool check_connekt(t_server *server_info, int pos) {
    server_info->table_users[pos].socket = accept(
            server_info->poll_set[0].fd, 0, 0);
    server_info->table_users[pos].ssl = SSL_new(server_info->ctx);
    SSL_set_fd(server_info->table_users[pos].ssl,
               server_info->table_users[pos].socket);
    if (SSL_accept(server_info->table_users[pos].ssl) == 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(server_info->table_users[pos].ssl);
        close(server_info->table_users[pos].socket);
        server_info->table_users[pos].socket = -1;
        mx_add_log(server_info, "ERROR new user DONT SSL connekt to server\n");
        return false;
    }
    return true;
}


static void dont_have_slot(t_server *server_info) {
    int fd = accept(server_info->poll_set[0].fd, 0, 0);

    close(fd);
    mx_add_log(server_info, "DON'T have slot to server\n");
}

int mx_accept_new_connect(t_server *server_info, int max_connect) {
    int pos = check_pos(server_info, max_connect);

    if (pos == 0) {
        dont_have_slot(server_info);
    }
    else {
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        if (check_connekt(server_info, pos)) {
            server_info->table_users[pos].id_users = 0;
            server_info->poll_set[pos].fd =
                server_info->table_users[pos].socket;
            server_info->poll_set[pos].events = POLLIN;
            server_info->poll_set[pos].revents = 0;
            if (pos == server_info->size_connekt)
                server_info->size_connekt++;
            mx_add_log(server_info, "ADD new user to server\n");
        }
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    return -1;
}
