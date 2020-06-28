#include "server.h"
#include "defines.h"

static int callback(void *param, int column, char **data, char **names) {
    char *respons;
    int sum;

    sum = 43 + strlen(data[4]);
    respons =  malloc(sizeof(char) * sum);
    memset(&respons[1], 0, 4);
    respons[0] = data[5][0] - '0';
    *((int*)&respons[5]) = sum;
    *((int*)&respons[9]) = atoi(data[0]);
    *((int*)&respons[13]) = atoi(data[1]);
    *((int*)&respons[17]) = atoi(data[2]);
    sprintf(&respons[21], "%s", data[3]);//42-21
    sprintf(&respons[41], "%s", data[6]);//62-21
    sprintf(&respons[42], "%s", data[4]);//63-21
    mx_write_socket(param, respons);
    free(respons);
    return 0;
}

char *mx_get_chat_msg(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int id_query = *(int*)&user->buff[1];

    if (mx_check_user_in_chat(*((int*)&user->buff[9]), user->id_users,
                              server_info) == 0)
        return mx_create_response(user->buff[0], id_query, MX_QS_ERR_RIGHT);
    if (*((int*)&user->buff[13]) == 0)
        *((int*)&user->buff[13]) = 2147483647;
    // if (strcmp(&user->buff[20], "0") == 0)
    //     sprintf(&user->buff[20], "%d", 2147483647);
    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_data, msg_status, msg_avatar from (select * from msg where"
            " msg_chat_id = '%d' and msg_status != 4 and msg_id < '%d' order"
            " by msg_id DESC LIMIT %d) order by msg_id ASC;", 
            *((int*)&user->buff[9]), *((int*)&user->buff[13]), 
            *((int*)&user->buff[17]));
    if (mx_do_query(sql, callback, user, server_info) != SQLITE_OK)
        return mx_create_response(user->buff[0], id_query, MQ_QS_ERR_SQL);
    return 0;
}