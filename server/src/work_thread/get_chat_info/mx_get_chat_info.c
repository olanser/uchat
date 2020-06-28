#include "server.h"
#include "defines.h"

static int callback(void *param, int column, char **data, char **names) {
    char *response = malloc(sizeof(char) * 122);

    memset(response, 0, 122);
    response[0] = 10;
    response[5] = 122;
    if (data[1][0] == '2')
        response[9] = '2';
    else
        response[9] = '1';
    sprintf(&response[10], "%s", data[2]);
    sprintf(&response[21], "%s", data[0]);
    *((char **)param) = response;
    return 0;
}

static int get_info_chat(t_server *server_info, t_server_users *user,
                         char **respons) {
    char sql[80];
    int a = 0;

    sprintf(sql, "select chat_name, chat_type, chat_id from chat where chat_id "
            "= '%s';", &user->buff[9]);
    a = mx_do_query(sql, callback, respons, server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}

char *mx_get_chat_info(t_server *server_info, t_server_users *user) {
    char sql[80];
    char *response = 0;

    if (mx_check_number(&user->buff[9], 11) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_FUNC);
    if (mx_check_user_in_chat(&user->buff[9], user->id_users, server_info) == 0)
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MX_QS_ERR_RIGHT);
    if (get_info_chat(server_info, user, &response))
        return mx_create_response(user->buff[0], *(int*)&user->buff[1],
                                  MQ_QS_ERR_SQL);
    if (response)
        return response;
    return 0;
}