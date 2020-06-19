#include "header.h"

/* return len of response */
int mx_get_msg_response_10(char status, char *request, char **response) {    
    int total_len = 10;

    *response = malloc(total_len);
    mx_memcpy(*response, request, 5);
    (*response)[9] = status;
    *(int*)(&(*response)[5]) = total_len;
    return total_len;
}