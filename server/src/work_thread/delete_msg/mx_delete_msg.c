#include "server.h"
#include "defines.h"


static char *create_response(int id_msg, int id_chat) {
    char *respons = malloc(sizeof(char) * 17);

    memset(respons, 0, 17);
    respons[0] = 4;
    respons[5] = 17;
    *((int*)&respons[9]) = id_msg;
    *((int*)&respons[13]) = id_chat;
    return respons;
}

static int delete_msg_to_db(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int a = 0;

    sprintf(sql, "update msg set msg_status='4', "
            "msg_send_time=datetime('now') where msg_id=%d;",
            *((int*)&user->buff[9]));
    a = mx_do_query(sql, 0, 0,server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}

char *mx_delete_msg(t_server *server_info, t_server_users *user) {
    char sql[100];
    char *response = 0;
    int query = *((int*)&user->buff[1]);

    if (mx_check_id_message_in_user(*(int*)&user->buff[9], 
        *(int*)&user->buff[13], server_info, user) == 0) {
        mx_add_error_work_log(server_info, user, MX_DONT_ID_MSG_IN_USER);
        return mx_create_response(user->buff[0], query, MX_QS_ERR_RIGHT);
    }
    if (delete_msg_to_db(server_info, user)) {
        mx_add_error_work_log(server_info, user, MX_SQL_ERROR);
        return mx_create_response(user->buff[0], query, MQ_QS_ERR_SQL);
    }
    sprintf(sql, "select cou_usr_id from cou where cou_chat_id = "
            "%d;", *(int*)&user->buff[13]);
    response = create_response(*((int*)&user->buff[9]),
                               *((int*)&user->buff[13]));
    mx_send_response_user(server_info, response, sql);
    free(response);
    return 0;
}