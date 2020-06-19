#include "header.h"
#include "mxinet.h"
#include "defines.h"

int mx_new_data_to_socket(t_server *server_info, int id) {
    char buffer[1024];
    int rc = recv(server_info->poll_set[id].fd, buffer, 9, 0);
    int len = 0;
    bool close_conn = false;

    if (rc < 0) {
        if (errno != EWOULDBLOCK) {
            perror("  recv() failed");
            close_conn = true;
        }
    }
    else if (rc == 0) {
        printf("Connection closed\n");
        close_conn = true;
    }    
    else if (buffer[0] > MX_QS_MAX_REQUEST) {
         printf("Wrong request  Connection closed\n");
         close_conn = true;
    }
    else if ((len =*((int *)(&buffer[5]))) > MX_QS_MAX_SIZE) {   // size
        printf("Wrong Size  Connection closed\n");
        close_conn = true;
    }
    else {
        rc = recv(server_info->poll_set[id].fd, buffer, len - rc, 0);
        len = rc;
        server_info->table_users[id].buff = strndup(buffer, rc);
        printf("  %d bytes received\n", len);
        server_info->poll_set[id].revents = 0;
        pthread_mutex_lock(&(server_info->m_works));
        mx_push_back(&(server_info->works), &(server_info->table_users[id]));
        pthread_mutex_unlock(&(server_info->m_works));
        //kill(getpid());
    }
    if (close_conn) {
        close(server_info->poll_set[id].fd);
        server_info->poll_set[id].fd = -1;
        server_info->compress_array = true;
    }
    return -1;
}
