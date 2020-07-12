#include "server.h"


char *mx_do_request(t_server *server_info, t_server_users *user) {
    char *(*api[])(t_server *, t_server_users *) = {
        mx_signup, mx_signin, mx_send_message, mx_edit_message,
        mx_delete_msg, mx_send_file, mx_get_user_info, mx_get_chat_users,
        mx_get_msgs_time, mx_show_users, mx_get_chat_info, 0,
        mx_get_chat_msg, mx_join_chat, mx_create_chat,
        mx_create_dialog, mx_leave_chat, mx_get_chats_info,
        mx_change_avatar, mx_create_unique_name, mx_send_file,
        mx_end_of_file, mx_get_file
    };
    char *(*foo)(t_server *, t_server_users *) = (*api[(int)user->buff[0]]);

    return foo(server_info, user);
}
