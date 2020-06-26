/* 
* Authour vbalachevs
* read socket and update database
*/
#include "client.h"
#include "libmx.h"
#include "mxinet.h"

int mx_read_head(int socket, char *head) {
    int c = read(socket, head, 9);

    if (c != 9) {
        fprintf(stderr, "READ ERROR!\n");
        close(socket);
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

void mx_listen(int socket, char **response) {
    char head[9];
    int status = 0;
    int size = mx_read_head(socket, head);

    if (size == -1)
        return;
    *response = init_response(size, head);
    mx_readn_sock(socket, &(*response)[9], size - 9);
}

void* mx_listener(void *data) {
    t_info* info = (t_info*)data;
    char *response = 0;

    while (1) {
        mx_listen(info->sock, &response);
        mx_handle_response(info, response);
        free(response);
    }

    return (void*)0;
}

