#include "header.h"

// int mx_delete_from_pd(char *pid) {
//     char sql[1024];

//     sprintf(sql, "delete from pd where pd_pid = %s;", pid);
//     return mx_do_query(sql, 0, 0);
// }

void mx_end_of_input(int socket) {
    struct sockaddr addr;
    socklen_t len = sizeof(addr);

    // mx_delete_from_pd(mx_itoa(getpid()));
    if (getsockname(socket, &addr, &len) == -1) {
        fprintf(stderr, "getsockname error: %s\n", strerror(errno));
        exit(1);
    }
    printf("server[%s]:\n", inet_ntoa(((struct sockaddr_in*)&addr)->sin_addr));
    printf("closed \n");
    exit(0);
}

/* 
* retunrn:
* MX_QS_ERR_SERV - if not enough params 
* MX_QS_OK - if ok
* exit (close process) - if connect closed
*/
unsigned char get_parametrs(int socket, char *params) {
    int len = read(socket, params, 9);
    if (len == 0) {
        mx_end_of_input(socket);
        exit(0);
    }
    if (len != 9) {
        return MX_QS_ERR_REQUEST;
    }
    return (char)MX_QS_OK;
}

char *init_request(int size, char *params) {
    char *new_request = malloc(sizeof(char) * size);
    mx_memcpy(new_request, params, 9); // save params
    printf("%d -- size\n", params[5]);
    printf("%d -- req\n", params[0]);
    return new_request;
}

char read_request(int socket, char* request, int size) {
    int count = 0;
    int curr = 9;

    while (curr < size) {
        count = read(socket, &request[curr], size - curr);
        
        if (count == -1 || count == 0) {
            mx_end_of_input(socket);
            exit(1);
        }
        curr += count;
    }
    return (char)MX_QS_OK;
}

char get_request(int socket, char **request, char *params) {
    int size = *(int*)(&params[5]);

    *request = init_request(size, params);
    read_request(socket, *request, size);
    return (char)MX_QS_OK;
}

/* 
* return status:
* MX_QS_OK - if all ok
* MX_QS_ERR_SERV - if error
*/
char mx_read_socket(int socket, char **request) {
    char params[9]; // type of query(1), id of query(4) and size(4)
    unsigned char status = 0;

    if (get_parametrs(socket, params) != MX_QS_OK) 
        return MX_QS_ERR_SERV;
    get_request(socket, request, params);
    return (char)MX_QS_OK;
}
