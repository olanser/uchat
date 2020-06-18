#include "header.h"


// int mx_send_message(void *request, t_user *user_info) {
//     // write(1, "SEND", 4);
//     return 0;
// }


int mx_do_request(char *request, char **response, t_user *user_info) {
    int (*api[])(void *, char **, t_user *) = {
            mx_signup, // 0 
            mx_signin, // 1
            mx_send_message, // 2 
            mx_editmessage, // 3 
            mx_delete_msg, // 4 
            mx_send_file, // 5 
            mx_get_user_info, // 6 
            mx_get_chat_users, // 7 
            mx_get_msgs_time, // 8 
            mx_show_users, // 9 
            mx_get_chat_info, // 10 
            0, // 11 
            mx_authenticate, // 12
            mx_join_chat, //13
            mx_create_chat, //14
            mx_create_dialog, //15
            mx_leave_chat //16s
    };
    ;
    int (*foo)(void *, char **, t_user *) =  (*api[request[0]]);
    return foo(request, response, user_info);
}

/*
* 0 if all good
* err status - 
*    if user dont registered 
*    and wanna do something or if wrong query
*/
static char get_status(char *request, t_user *user_info) {
    if (user_info->id == 0) { // unregistered
        if (request[0] != 0 && request[0] != 1 && request[0] != 12) {
            return MX_QS_ERR_RIGHT;
        }
    }
    if (request[0] > MX_COUNT_FUCTIONS) {
        return MX_QS_ERR_FUNC;
    }
    return 0;
}

int set_status(char *request, char **response, char status) {
    *response = malloc(sizeof(char) * 10);
    mx_memcpy(*response,  request, 5);
    *(int*)(&(*response)[5]) = 10; // set size
    (*response)[9] = status;
    return 10;
}

/* 
* 0 if all good
* len if some err
*/
int mx_check_request(char *request, char **response, t_user *user_info) {
    char status = get_status(request, user_info);

    if (status != 0) {
        return set_status(request, response, status);
    }
    return 0;
}

/*
* return:
* length of response
*/
int mx_handle_input(char *request, char **response, t_user *user_info) {
    int i = 0;
    int count = mx_check_request(request, response, user_info);

    if (count != 0) { // have length of error message
        return count;
    }
    else { // have not error
        count = mx_do_request(request, response, user_info);
    }
    return count;
}
