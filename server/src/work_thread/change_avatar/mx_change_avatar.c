#include "server.h"
#include "defines.h"

static char *create_response(t_server_users *user) {
    char *response = malloc(11);

    memset(response, 0, 11);
    response[0] = user->buff[0];
    *((int*)&response[1]) = *((int*)&user->buff[1]);
    *((int*)&response[5]) = 11;
    response[9] = (char)200;
    response[10] = user->buff[9];
    return response;
}

char *mx_change_avatar(t_server *server_info, t_server_users *user) {
    char sql[1024];
    char *response;

    if (mx_check_avatar(user->buff[9]) == 0)
        return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
                                  MX_QS_ERR_FUNC);
    sprintf(sql, "update user set user_avatar='%c' where usr_id=%d",
            user->buff[9], user->id_users);
    if (mx_do_query(sql, 0, 0,server_info) != SQLITE_OK)
    return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
                                  MQ_QS_ERR_SQL);
    sprintf(sql, "update msg set msg_avatar='%c' where msg_creator=%d",
            user->buff[9], user->id_users);
    printf("%s\n", sql);
    if (mx_do_query(sql, 0, 0,server_info) != SQLITE_OK)
    return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
                                  MQ_QS_ERR_SQL);
    return create_response(user);
}
