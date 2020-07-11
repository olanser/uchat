/* 
* Authour vbalachevs
* read socket and update database
*/
#include "client.h"
#include "libmx.h"
#include "mxinet.h"

int mx_read_head(t_info* info, char *head) {
    int c = SSL_read(info->ssl, head, 9);

    if (c != 9) {
        fprintf(stderr, "READ ERROR!\n");
        SSL_free(info->ssl); 
        close(info->sock);
        exit(1);
        return -1;
    }
    return *(int*)(&head[5]);
}

char *init_response(int size, char *params) {
    char *new_request = malloc(sizeof(char) * size);
    mx_memcpy(new_request, params, 9); // save params
    return new_request;
}

int mx_readn_sock_(t_info* info, char *response, int size) {
    int count = 0;
    int curr = 0;

    while (curr < size) {
        count = SSL_read(info->ssl, &response[curr], size - curr);
        if (count == -1 || count == 0) {
            fprintf(stderr, "SERVER CLOSED!\n");
            SSL_free(info->ssl); 
            close(info->sock);
            exit(1);
        }
        curr += count;
    }
    return 0;
}


void mx_listen(t_info* info, char **response) {
    char head[9];
    int status = 0;
    int size = mx_read_head(info, head);

    if (size == -1)
        return;
    *response = init_response(size, head);
    mx_readn_sock_(info, &(*response)[9], size - 9);
}

void* mx_listener(void *data) {
    t_info* info = (t_info*)data;
    char *response = 0;

    while (1) {
        mx_listen(info, &response);
        mx_handle_response(info, response);
        free(response);
    }
    return (void*)0;
}

