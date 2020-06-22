#include "server.h"

bool mx_check_id_message_in_user(char *id_message, char *id_chat,
    t_server *server_info, t_server_users *user) {
    char sql[1024];
    int check = 0; 

    sprintf(sql, "select * from msg where msg_id='%s'and msg_creator='%s' and "
            "msg_status!=4 and msg_chat_id = '%s';", id_message,
            user->id_users, id_chat);
    mx_do_query(sql, mx_callback_count, &check, server_info);
    if (check == 0)
        return 0;
    return 1;
}
