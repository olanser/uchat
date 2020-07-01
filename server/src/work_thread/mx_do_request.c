#include "server.h"


char *mx_do_request(t_server *server_info, t_server_users *user) {
    printf("HERE - %d\n", user->buff[0]);
    char *(*api[])(t_server *, t_server_users *) = {
            mx_signup, // 0 +
            mx_signin, // 1 +
            mx_send_message, // 2 +
            mx_edit_message, // 3 +
            mx_delete_msg, // 4 +
            mx_send_file, // 5
            mx_get_user_info, // 6 +
            mx_get_chat_users, // 7 +
            mx_get_msgs_time, // 8 +
            mx_show_users, // 9 +
            mx_get_chat_info, // 10 +
            0, // 11
            mx_get_chat_msg, // 12
            mx_join_chat, //13 +
            mx_create_chat, //14 +
            mx_create_dialog, //15 +
            mx_leave_chat, //16 +
            mx_get_chats_info, // 17
            mx_change_avatar, // 18
            mx_create_unique_name, //19
            mx_send_file, //20
            mx_end_of_file //21
            //mx_get_file
    };
    char *(*foo)(t_server *, t_server_users *) = (*api[user->buff[0]]);
    return foo(server_info, user);
}
