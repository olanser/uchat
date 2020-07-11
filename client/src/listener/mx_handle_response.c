#include "client.h"
#include "defines_client.h"

static int check(t_info *info, char *response) {
    if (info->user_info == 0 && response[0] > 1) {
        fprintf(stderr, "Need authorizied, query #%d\n", response[0]);
        return 1;
    }
    if (response[0] > MX_COUNT_API) {
        fprintf(stderr, "Error API number: %d\n", response[0]);
        return 1;
    }
    return 0;
}

int mx_handle_response(t_info *info, char *response) {
    int (*handlers[])(char *, t_info *) = {
        mx_h_signup, mx_h_signin, mx_h_send_msg, mx_h_edit_msg, // 3
        mx_h_delete_msg, mx_h_send_file, mx_h_get_user_info, 
        mx_h_get_chat_users, mx_h_get_msgs_time, mx_h_show_users, // 9
        mx_h_get_chat_info, mx_h_get_file, mx_h_authenticate, 
        mx_h_join_chat, mx_h_create_chat, mx_h_create_dialog, // 15
        mx_h_leave_chat, mx_h_get_chats_info, mx_h_who_is_that, // 18
        mx_h_get_unique_name, mx_h_who_is_that, mx_h_who_is_that, //21
        mx_h_get_file, mx_h_who_is_that //23
    };
    int (*foo)(char *, t_info *) = 0;
    if (check(info, response) == 1)
        return -1;
    printf("number of query = %d // mx_handle_response\n", response[0]);
    foo =  (*handlers[response[0]]);
    return foo(response, info);
}
