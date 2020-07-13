#include "server.h"
#include "defines.h"

static void rename_file(t_server *server_info, t_server_users *user,
                        t_file_message *message) {
    char sql_request[1024];
    char name[256];

    sprintf(sql_request, "SELECT msg_id from msg where msg_creator = '%d'"
            " ORDER by msg_id DESC LIMIT 1;", user->id_users);
    mx_do_query(sql_request, mx_return_one_str, &(message->id_message),
                server_info);
    sprintf(sql_request, "%s/%s", MX_DIR_DOWNLOAD, message->unique_name);
    sprintf(name, "%s/%s", MX_DIR_DOWNLOAD, message->id_message);
    rename(sql_request, name);
    free(message->unique_name);
    free(message->id_message);
}


void mx_creat_msg_to_database_and_rename_file(t_server *server_info,
    t_server_users *user, t_file_message *message) {
    char sql[1024];

    sprintf(sql, "INSERT INTO msg (msg_creator, msg_send_time, msg_file_type,"
        " msg_chat_id, msg_file_size, msg_status, msg_file_name, msg_avatar, "
        "msg_type) VALUES (%d, datetime('now'), %d, %d, %d, %s, '%s', '%c', "
        "%d);", user->id_users, message->file_type, message->id_chat,
        message->size, "5", message->true_name, message->avatar, 3);
    mx_do_query(sql, 0, 0, server_info);
    rename_file(server_info, user, message);
}