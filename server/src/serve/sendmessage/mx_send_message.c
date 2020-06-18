#include "header.h"

static char *create_sql_request(t_table_message message, t_user *user_info) {
    char *command =  mx_strjoin("INSERT INTO msg (msg_creator, msg_send_time, msg_data, msg_chat_id) VALUES (", user_info->id);

    command =  mx_strjoin2(command, ", datetime('now'), \'");
    command =  mx_strjoin_len(command, message.data, message.size - 20);
    command =  mx_strjoin2(command, "\',");
    command =  mx_strjoin2(command, message.id_chat);
    command =  mx_strjoin2(command, ");");
    return command;
}

int mx_send_message(void *request, char **response, t_user *user_info) {
    t_table_message message;
    char *sql_request = 0;

    mx_create_response(request, response);
    if (mx_check_message(((char*)request), &message) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        (*response)[9] = (char)100;
        return 10;
    }
    if (mx_check_user_in_char(message.id_chat, user_info->id) == 0) {
        fprintf(MX_ERROR_THREAD, "permission\n");
        (*response)[9] = (char)103;
        return 10;
    }
    sql_request = create_sql_request(message, user_info);
    if (sql_request && mx_do_query(sql_request,0,0) == 0) {
        free(sql_request);
        (*response)[9] = (char)200;
        mx_create_signal_new_message(message.id_chat);
        return 10;
    }
    free(sql_request);
    (*response)[9] = (char)100;
    return 10;
}
