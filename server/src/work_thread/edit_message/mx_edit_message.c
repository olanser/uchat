#include "server.h"
#include "defines.h"

static int edit_msg_to_db(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int a = 0;

    sprintf(sql, "update msg set msg_data='%s', msg_status='3', msg_avatar=%c"
            ", msg_send_time=datetime('now') where msg_id=%d;",
            &user->buff[18], user->buff[17], *((int*)&user->buff[13]));
    a = mx_do_query(sql, 0, 0,server_info);
    if (a != SQLITE_OK)
        return 1;
    return 0;
}


static int callback(void *data, int column, char **name, char **tabledata) {
    int sum = 47 + strlen(name[5]);
    char *response =  malloc(sizeof(char) * sum);

    memset(&response[1], 0, 4);
    response[0] = 3;
    *((int*)&response[5]) = sum;
    *((int*)&response[9]) = atoi(name[0]);
    *((int*)&response[13]) = atoi(name[1]);
    *((int*)&response[17]) = atoi(name[2]);
    sprintf(&response[21], "%s",name[3]);
    sprintf(&response[41], "%s",name[4]);
    *((int*)&response[42]) = atoi(name[6]);
    sprintf(&response[46], "%s",name[5]);
    *(char**)data = response;
    return 0;
}

static char *create_response_to_users(t_server *server_info,
                                      t_server_users *user) {
    char *respons = 0;
    char sql[1024];

    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_avatar, msg_data, msg_type from msg where msg_creator = "
            "%d and msg_status = 3 and msg_chat_id = %d and msg_data = '%s' "
            "ORDER by msg_id DESC LIMIT 1;", user->id_users,
            *((int*)&user->buff[9]), &user->buff[18]);
    mx_do_query(sql, callback, &respons, server_info);
    return respons;
}

static char *check_query(t_server *server_info, t_server_users *user) {
    int query = *((int*)&user->buff[1]);
    char log[1024];

    if (user->buff[*((int*)(&user->buff[5])) - 1] != 0) {
        mx_add_error_work_log(server_info, user, MX_ERROR_END_STR);
        return mx_create_response(user->buff[0], query, MX_QS_ERR_FUNC);
    }
    if (mx_check_avatar(user->buff[17]) == 0) {
        mx_add_error_work_log(server_info, user, MX_EROR_ID_AVATAR);
        return mx_create_response(user->buff[0], query, MX_QS_ERR_FUNC);
    }
    if (mx_check_id_message_in_user(*((int*)&user->buff[13]),
        *(int*)&user->buff[9], server_info, user) == 0) {
        mx_add_error_work_log(server_info, user, MX_DONT_ID_MSG_IN_USER);
        return mx_create_response(user->buff[0], query, MX_QS_ERR_RIGHT);
        }
    return 0;
}

char *mx_edit_message(t_server *server_info, t_server_users *user) {
    char *respons = 0;
    char sql[100];


    respons = check_query(server_info, user);
    if (respons)
        return respons;
    if (edit_msg_to_db(server_info, user)) {
        mx_add_error_work_log(server_info, user, MX_SQL_ERROR);
        return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
                                  MQ_QS_ERR_SQL);
    }
    respons = create_response_to_users(server_info, user);
    if (respons) {
        sprintf(sql, "select cou_usr_id from cou where cou_chat_id = %d;",
                *((int*)&user->buff[9]));
        mx_send_response_user(server_info, respons, sql);
        free(respons);
    }
    return 0;
}
