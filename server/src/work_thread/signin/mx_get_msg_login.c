#include "server.h"
#include "defines.h"

static int get_ok_msg(char **response, t_table_user *tuser) {
    int size = 218;

    *response = malloc(sizeof(char) * size);
    memset(*response, 0, size);
    (*response)[9] = (char)200;
    *((int*)(&(*response)[10])) = tuser->id;
    mx_strcpy(&(*response)[14], tuser->first_name);
    mx_strcpy(&(*response)[65], tuser->second_name);
    mx_strcpy(&(*response)[116], tuser->nickname);
    (*response)[217] = tuser->avatar;
    return size;
}

static int get_err_msg(char **response, char status) {
    int total_len = 10;

    *response = malloc(total_len);
    return total_len;
}

/* return len of response */
int mx_get_msg_login(char status, char *request, t_table_user *tuser,
                    char **response) {    
    int total_len = 0;

    if (status == (char)MX_QS_OK) {
        total_len = get_ok_msg(response, tuser);
    }
    else {
        total_len = get_err_msg(response, status);
    }
    mx_memcpy(*response, request, 5);
    (*response)[9] = status;
    *((int*)(&(*response)[5])) = total_len;
    return total_len;
}