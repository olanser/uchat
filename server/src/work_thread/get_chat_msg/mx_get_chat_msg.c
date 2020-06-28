#include "server.h"
#include "defines.h"

static int callback(void *param, int column, char **data, char **names) {
    char *respons;
    int sum;

    if (data[5][0] == '4')
        return 0;
    else {
        sum = 64 + strlen(data[4]);
        respons =  malloc(sizeof(char) * sum);
        memset(respons, 0, sum);
        respons[0] = data[5][0] - '0';
        *(int*)&respons[5] = sum;
        sprintf(&respons[9], "%s", data[0]);
        sprintf(&respons[20], "%s", data[1]);
        sprintf(&respons[31], "%s", data[2]);
        sprintf(&respons[42], "%s", data[3]);
        sprintf(&respons[62], "%s", data[6]);
        sprintf(&respons[63], "%s", data[4]);
    }
    mx_write_socket(param, respons);
    free(respons);
    return 0;
}

char *mx_get_chat_msg(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int id_query = *(int*)&user->buff[1];

    if (mx_check_number(&user->buff[9], 11) == 0
        || mx_check_number(&user->buff[20], 11) == 0)
        return mx_create_response(user->buff[0], id_query, MX_QS_ERR_FUNC);
    if (mx_check_user_in_chat(&user->buff[9], user->id_users, server_info) == 0)
        return mx_create_response(user->buff[0], id_query, MX_QS_ERR_RIGHT);
    if (strcmp(&user->buff[20], "0") == 0)
        sprintf(&user->buff[20], "%d", 2147483647);
    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_data, msg_status, msg_avatar from (select * from msg where"
            " msg_chat_id = '%s' and msg_status != 4 and msg_id < '%s' order by msg_id DESC LIMIT "
            "%d) order by msg_id ASC;", &user->buff[9], &user->buff[20],
            *(int*)&user->buff[31]);
    if (mx_do_query(sql, callback, user, server_info) != SQLITE_OK)
        return mx_create_response(user->buff[0], id_query, MQ_QS_ERR_SQL);
    return 0;
}