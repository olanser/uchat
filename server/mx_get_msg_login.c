#include "header.h"

static int get_ok_msg(char **response, t_table_user *tuser) {
    int i = 10;
    int lens[4] = {mx_strlen(tuser->id),
        mx_strlen(tuser->first_name), 
        mx_strlen(tuser->second_name),
        mx_strlen(tuser->nickname)};
    int total_len = 11 + lens[0] + lens[1] + lens[2] + 13;

    *response = malloc(total_len);
    memset(&(*response)[10], 0, 11);
    mx_memcpy(&(*response)[10], tuser->id, lens[0]);
    i += 11;
    mx_memcpy(&(*response)[21], tuser->first_name, lens[1] + 1);
    i += mx_strlen(tuser->first_name) + 1;
    mx_memcpy(&(*response)[i], tuser->second_name, lens[2] + 1);
    i += mx_strlen(tuser->second_name) + 1;
    mx_memcpy(&(*response)[i], tuser->nickname, lens[3] + 1);
    return total_len;
}

static int get_err_msg(char **response, char status) {
    int total_len = 10;

    *response = malloc(total_len);
    return total_len;
}

/* return len of response */
int mx_get_msg_login(char status, char *request, t_table_user *tuser, char **response) {    
    int total_len = 0;

    if (status == (char)MX_QS_OK) {
        total_len = get_ok_msg(response, tuser);
    }
    else {
        total_len = get_err_msg(response, status);
    }
    // memset(*response, 0, total_len);
    mx_memcpy(*response, request, 5);
    (*response)[9] = status;
    *(int*)(&(*response)[5]) = total_len;
    return total_len;
}