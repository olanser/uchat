#include "server.h"
#include "mxinet.h"
#include "defines.h"

static bool error_case(bool *close_conn, int rc, char *buffer) {
    if (rc < 0) {
        if (errno != EWOULDBLOCK) {
            perror("recv() failed");
            *close_conn = true;
        }
    }
    else if (rc == 0) {
        printf("Connection closed\n");
        *close_conn = true;
    }
    else if (buffer[0] > MX_COUNT_FUCTIONS) {
        printf("Wrong request  Connection closed\n");
        *close_conn = true;
    }
    else if ((rc =*((int *)(&buffer[5]))) > MX_MAX_SIZE_REQUEST) {
        printf("Wrong Size  Connection closed\n");
        *close_conn = true;
    }
    return *close_conn;
}

static void read_socket(t_server *server_info, int id, char **buffer) {
    int len = *(int*)(&(*buffer)[5]);
    char log[MX_MAX_SIZE_REQUEST];

    if (len != 9)
        SSL_read(server_info->table_users[id].ssl, &(*buffer)[9], len - 9);
    server_info->table_users[id].buff = *buffer;
    *buffer = 0;
    server_info->poll_set[id].revents = 0;
    server_info->table_users[id].work = true;
    pthread_mutex_lock(&(server_info->m_works));
    mx_push_back(&(server_info->works), &(server_info->table_users[id]));
    sprintf(log, "ADD NEW WORK USER = %d and API = %d\n", 
            server_info->table_users[id].id_users,
            server_info->table_users[id].buff[0]);
    mx_add_log(server_info, log);
    pthread_mutex_unlock(&(server_info->m_works));
    kill(getpid(), SIGUSR1);
}

static void free_user_connection_close(t_server *server_info, int id) {
    close(server_info->poll_set[id].fd);
    SSL_free(server_info->table_users[id].ssl);
    server_info->poll_set[id].fd = -1;
    server_info->table_users[id].socket = -1;
    server_info->table_users[id].id_users = 0;
    server_info->poll_set[id].events = 0;
    server_info->compress_array = true;
}

int mx_new_data_to_socket(t_server *server_info, int id) {
    char *buffer = malloc(sizeof(char) * MX_MAX_SIZE_REQUEST);
    int rc = SSL_read(server_info->table_users[id].ssl, buffer, 9);
    bool close_conn = false;
    char log[100];

    if (error_case(&close_conn, rc, buffer));
    else
        read_socket(server_info, id , &buffer);
    if (close_conn) {
        sprintf(log, "CLOSE CONNEKT USER = %d\n",
                server_info->table_users[id].id_users);
        mx_add_log(server_info, log);
        pthread_rwlock_wrlock(&(server_info->m_edit_users));
        free_user_connection_close(server_info, id);
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    if (buffer)
        free(buffer);
    return -1;
}
