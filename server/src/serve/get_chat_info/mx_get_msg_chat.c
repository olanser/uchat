#include "header.h"

static int get_ok_msg(char **response, char *request, void *data) {
    int i = 10;
    int lens = mx_strlen(((char**)((void**)data)[1])[0]);
    int total_len = lens + 22;

    *response = malloc(total_len);
    memset(*response, 0, total_len);
    mx_memcpy(&(*response)[10], &request[9], 10);
    mx_memcpy(&(*response)[21], ((char**)((void**)data)[1])[0], lens + 1);
    return total_len;
}

static int get_err_msg(char **response, char status) {
    int total_len = 10;

    *response = malloc(total_len);
    return total_len;
}

/* return len of response */
int mx_get_msg_chat(char status, char *request, void *data, char **response) {    
    int total_len = 0;

    if (status == (char)MX_QS_OK) {
        total_len = get_ok_msg(response, request, data);
    }
    else {
        total_len = get_err_msg(response, status);
    }
    mx_memcpy(*response, request, 5);
    (*response)[9] = status;
    if (status == (char)MX_QS_OK)
        (*response)[9] = ((char**)((void**)data)[2])[0][0];
    free(((char**)((void**)data)[1])[0]);
    *(int*)(&(*response)[5]) = total_len;
    return total_len;
}