#include "server.h"
#include "defines.h"

static int add_msg_to_db(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int a = 0;
    sprintf(sql, "INSERT INTO msg (msg_creator, msg_send_time, msg_data, "
            "msg_chat_id, msg_avatar) VALUES (%s, datetime('now'), \'%s\', %s,"
            " %c);", user->id_users, &user->buff[21], &user->buff[9],
            user->buff[20]);
    a = mx_do_query(sql, 0, 0,server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}


static int callback(void *data, int column, char **name, char **tabledata) {
    int sum = 64 + strlen(name[5]);
    char *response =  malloc(sizeof(char) * sum);

    memset(response, 0, sum);
    response[0] = 2;
    *(int*)&response[5] = sum;
    sprintf(&response[9], "%s",name[0]);
    sprintf(&response[20], "%s",name[1]);
    sprintf(&response[31], "%s",name[2]);
    sprintf(&response[42], "%s",name[3]);
    sprintf(&response[62], "%s",name[4]);
    sprintf(&response[63], "%s",name[5]);
    *(char**)data = response;
    return 0;
}

static char *create_response_to_users(t_server *server_info, t_server_users *user) {
    char *respons = 0;
    char sql[1024];

    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_avatar, msg_data from msg where msg_creator = %s and "
            "msg_status = 2 and msg_chat_id = %s and msg_data = '%s' ORDER by "
            "msg_id DESC LIMIT 1;", user->id_users, &user->buff[9],
            &user->buff[21]);
    mx_do_query(sql, callback, &respons, server_info);
    // if (respons) {
        // printf("Response = %s %s %s %s %s %s\n", &respons[9], &respons[20], &respons[31],
        //         &respons[42], &respons[62], &respons[63]);
    // }
    return respons;
}

char *mx_send_message(t_server *server_info, t_server_users *user) {
    char *respons = 0;
    char sql[100];

    if (user->buff[*(int*)(&user->buff[5]) - 1] != 0) {
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_FUNC);
    }
    if (mx_check_number(&user->buff[9], 11) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_FUNC);
    if (mx_check_user_in_chat(&user->buff[9], user->id_users, server_info) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_RIGHT);
    if (add_msg_to_db(server_info, user))
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MQ_QS_ERR_SQL);
    respons = create_response_to_users(server_info, user);
    if (respons) {
        sprintf(sql, "select cou_usr_id from cou where cou_chat_id = "
                "%s;", &user->buff[9]);
        mx_send_response_user(server_info, respons, sql);
        free(respons);
    }
    return 0;
}
