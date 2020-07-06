#include "server.h"
#include "defines.h"

static int add_msg_to_db(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int a = 0;

    sprintf(sql, "INSERT INTO msg (msg_creator, msg_send_time, msg_data, "
            "msg_chat_id, msg_avatar, msg_type) VALUES (%d, datetime('now'"
            "), \'%s\', %d, %c, %d);", user->id_users, &user->buff[18],
            *((int*)&user->buff[9]), user->buff[13], *((int*)&user->buff[14]));
    a = mx_do_query(sql, 0, 0, server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}


static int callback(void *data, int column, char **name, char **tabledata) {
    int sum = 47 + strlen(name[6]);
    char *response =  malloc(sizeof(char) * sum);

    memset(&response[1], 0, 4);
    response[0] = 2;
    *((int*)&response[5]) = sum;
    *((int*)&response[9]) = atoi(name[0]);
    *((int*)&response[13]) = atoi(name[1]);
    *((int*)&response[17]) = atoi(name[2]);
    sprintf(&response[21], "%s",name[3]);
    sprintf(&response[41], "%s",name[4]);
    *((int*)&response[42]) = atoi(name[5]);
    sprintf(&response[46], "%s",name[6]);
    *(char**)data = response;
    return 0;
}

static char *create_response_to_users(t_server *server_info,
                                      t_server_users *user) {
    char *respons = 0;
    char sql[1024];

    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_avatar, msg_type, msg_data from msg where msg_creator = "
            "%d and msg_status = 2 and msg_chat_id = %d and msg_data = '%s' "
            "ORDER by msg_id DESC LIMIT 1;", user->id_users,
            *((int*)&user->buff[9]), &user->buff[18]);
    mx_do_query(sql, callback, &respons, server_info);
    return respons;
}


static char *check_query(t_server *server_info, t_server_users *user) {
    int query = *((int*)&user->buff[1]);
    char log[1024];

    if (user->buff[*((int*)(&user->buff[5])) - 1] != 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_ERROR_END_STR, MX_QS_ERR_FUNC);
    if (*((int*)(&user->buff[14])) > 10)
        return mx_create_respons_error_and_log(server_info, user,
            "ERROR TYPE!! ", MX_QS_ERR_FUNC);
    if (mx_check_avatar(user->buff[13]) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_EROR_ID_AVATAR, MX_QS_ERR_FUNC);
    if (mx_check_user_in_chat(*((int*)&user->buff[9]), user->id_users,
                            server_info) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_DONT_HAVE_CHAT_USER, MX_QS_ERR_RIGHT);
    return 0;
}

char *mx_send_message(t_server *server_info, t_server_users *user) {
    char *respons = 0;
    char sql[100];

    respons = check_query(server_info, user);
    if (respons)
        return respons;
    if (add_msg_to_db(server_info, user))
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    respons = create_response_to_users(server_info, user);
    if (respons) {
        sprintf(sql, "select cou_usr_id from cou where cou_chat_id = "
                "%d;", *((int*)&user->buff[9]));
        mx_send_response_user(server_info, respons, sql);
        free(respons);
    }
    return 0;
}
