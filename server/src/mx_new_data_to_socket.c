#include "header.h"
#include "mxinet.h"
#include "defines.h"

int mx_new_data_to_socket(t_server *server_info, int id) {
    char *buffer = malloc(sizeof(char) * 1024);
    int rc = recv(server_info->poll_set[id].fd, buffer, 9, 0);
    int len = 0;

    if (rc < 0) {
        if (errno != EWOULDBLOCK) {
            perror("  recv() failed");
    
        }
    }
    else if (rc == 0) {
        printf("Connection closed\n");
    }    
    else if (buffer[0] > MX_QS_MAX_REQUEST) {
         printf("Wrong request  Connection closed\n");
    }
    else if ((len =*((int *)(&buffer[5]))) > MX_QS_MAX_SIZE) {   // size
        printf("Wrong Size  Connection closed\n");
    }
    else {
        rc = recv(server_info->poll_set[id].fd, &buffer[9], len - rc, 0);
        len = rc;
        bool check = false;
        server_info->table_users[id].buff = buffer;
        // printf("  %d bytes received\n", len + 9);
        pthread_mutex_lock(&(server_info->m_works));
        if (!server_info->works)
            check = true;
        mx_push_back(&(server_info->works), &(server_info->table_users[id]));
        pthread_mutex_unlock(&(server_info->m_works));
        if (check)
        kill(getpid(), SIGUSR1);
        printf("GET SIGNAL\n");
        server_info->poll_set[id].events = 0;
    }
    return -1;
}
