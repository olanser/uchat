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

static char *create_resp_send_edit(char **data) {
    int sum = 43 + strlen(data[4]);
    char *respons = malloc(sizeof(char) * sum);

    memset(respons, 0, 5);
    respons[0] = data[5][0] - '0';
    *((int*)&respons[5]) = sum;
    *((int*)&respons[9]) = atoi(data[0]);
    *((int*)&respons[13]) = atoi(data[1]);
    *((int*)&respons[17]) = atoi(data[2]);
    sprintf(&respons[21], "%s", data[3]);
    sprintf(&respons[41], "%s", data[6]);
    *((int*)&respons[42]) = atoi(data[7]);
    sprintf(&respons[46], "%s", data[4]);
    return respons;
}

static int callback(void *param, int column, char **data, char **names) {
    char *respons;

    if (data[5][0] == '4') {
        respons =  malloc(sizeof(char) * 13);
        memset(respons, 0, 5);
        respons[0] = 4;
        *((int*)&respons[5]) = 13;
        *((int*)&respons[9]) = atoi(data[0]);
    }
    else {
        respons =  create_resp_send_edit(data);
    }
    mx_write_socket(param, respons);
    free(respons);
    return 0;
}

char *mx_get_msgs_time(t_server *server_info, t_server_users *user) {
    char sql[1024];

    if (check_time(&user->buff[9]))
        return mx_create_respons_error_and_log(server_info, user, "ERROR TIME "
            "FORM!!", MX_QS_ERR_FUNC);
    sprintf(sql, "select msg.msg_id, msg.msg_chat_id, msg.msg_creator, "
        "msg.msg_send_time, msg.msg_data, msg.msg_status, msg.msg_avatar, ms"
        "g_file_type from msg where msg.msg_chat_id in (select cou.cou_chat_id "
        " from cou where cou.cou_usr_id == %d) and msg.msg_send_time >= '%s';",
        user->id_users, &user->buff[9]);
    if (mx_do_query(sql, callback, user, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    return 0;
}
