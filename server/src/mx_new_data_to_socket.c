#include "header.h"
#include "mxinet.h"
#include "defines.h"

static bool error_case(bool *close_conn, int rc, char *buffer) {
    if (rc < 0) {
        if (errno != EWOULDBLOCK) {
            perror("  recv() failed");
            *close_conn = true;
        }
    }
    else if (rc == 0) {
        printf("Connection closed\n");
        *close_conn = true;
    }
    else if (buffer[0] > MX_QS_MAX_REQUEST) {
        printf("Wrong request  Connection closed\n");
        *close_conn = true;
    }
    else if ((rc =*((int *)(&buffer[5]))) > MX_QS_MAX_SIZE) {   // size
        printf("Wrong Size  Connection closed\n");
        *close_conn = true;
    }
    return *close_conn;
}

static void read_socket(t_server *server_info, int id, char **buffer, int rc) {
    rc = recv(server_info->poll_set[id].fd, &(*buffer)[9], rc - 9, 0);
    server_info->table_users[id].buff = *buffer;
    *buffer = 0;
    server_info->poll_set[id].revents = 0;
    server_info->table_users[id].work = true;
    pthread_mutex_lock(&(server_info->m_works));
    mx_push_back(&(server_info->works), &(server_info->table_users[id]));
    pthread_mutex_unlock(&(server_info->m_works));
    kill(getpid(), SIGUSR1);
}

int mx_new_data_to_socket(t_server *server_info, int id) {
    char *buffer = malloc(sizeof(char) * 1024);
    int rc = recv(server_info->poll_set[id].fd, buffer, 9, 0);
    bool close_conn = false;

    if (error_case(&close_conn, rc, buffer));
    else
        read_socket(server_info, id , &buffer, rc);
    if (close_conn) {
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        close(server_info->poll_set[id].fd);
        server_info->poll_set[id].fd = -1;
        server_info->table_users[id].socket = -1;
        server_info->compress_array = true;
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    if (buffer)
        free(buffer);
    return -1;
}
