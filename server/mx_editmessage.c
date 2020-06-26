#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

static bool check_id_message_in_user(char *id_message, char *id_chat, t_user *user_info) {
    char sql[1024];
    int check = 0; 

    sprintf(sql, "select * from msg where msg_id='%s'and msg_creator='%s' and msg_status!=4 and msg_chat_id = '%s'", id_message, user_info->id, id_chat);
    mx_do_query(sql, callback, &check);
    if (check == 0)
        return 0;
    return 1;
}

int mx_editmessage(void *request, char **response, t_user *user_info) {
    char sql[1024];

    mx_create_response(request, response);
    if (mx_check_number(&request[9], 11) == 0 || mx_check_number(&request[20], 11) == 0 ) {
        printf("not id message\n");
        (*response)[9] = (char)100;
        return 10;
    }
    if (check_id_message_in_user(&request[9], &request[20], user_info) == 0) {
        printf("permission\n");
        (*response)[9] = (char)103;
        return 10;
    }
    sprintf(sql, "update msg set msg_data='%s', msg_status='3', msg_send_time=datetime('now') where msg_id='%s';", &request[31], &request[9]);
    mx_do_query(sql, 0, 0);
    mx_create_signal_new_message(&request[20]);
    (*response)[9] = (char)100;
    return 10;
}