#include "server.h"
#include "defines.h"

static bool check_time(char *time) {
    for (int i = 0; i < 20; i++) {
        if (i == 4 || i == 7) { 
            if (time[i] != '-')
                return 1;
        }
        else if (i == 10) {
            if (time[i] != ' ')
            return 1;
        }
        else if (i == 13 || i == 16) {
            if (time[i] != ':')
                return 1;
        }
        else if (i == 19) {
            if (time[i] == 0)
            return 0;
        }
        else if (time[i] < '0' || time[i] > '9') {
            return 1;
        }
    }
    return 1;
}

static int callback(void *param, int columns, char **data, char **names) {
    char *respons;
    int sum;

    if (data[5][0] == '4') {
        respons =  malloc(sizeof(char) * 20);
        memset(respons, 0, 20);
        respons[0] = 4;
        respons[5] = 20;
        sprintf(&respons[9], "%s", data[0]);
    }
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

char *mx_get_msgs_time(t_server *server_info, t_server_users *user) {
    char sql[1024];

    if (check_time(&user->buff[9]))
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_FUNC);
    sprintf(sql, "select msg.msg_id, msg.msg_chat_id, msg.msg_creator, "
        "msg.msg_send_time, msg.msg_data, msg.msg_status, msg.msg_status_see "
        "from msg where msg.msg_chat_id in (select cou.cou_char_id  from cou "
        "where cou.cou_usr_id == %s) and msg.msg_send_time >= '%s';",
        user->id_users, &user->buff[9]);
    
    if (mx_do_query(sql, callback, user, server_info) != SQLITE_OK) {
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MQ_QS_ERR_SQL);
    }
    return 0;
}
