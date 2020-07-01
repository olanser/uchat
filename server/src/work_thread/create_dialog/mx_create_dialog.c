#include "server.h"
#include "defines.h"


static char *create_response_create_dialog(char **temp, char *request) {
    int total_len = 17;
    char *respons = malloc(total_len);

    mx_memcpy(respons, request, 5);
    *(int*)(&(respons)[5]) = total_len;
    *(int*)(&(respons)[9]) = atoi(*temp);
     *(int*)(&(respons)[13]) = *(int*)(&(request)[5]);
    free(*temp);
    return respons;
}

static char *check_users(t_server *server_info,
                                    t_server_users *user) {
    char sql[1024];
    char *temp = 0;
    int id_query = *(int*)&user->buff[1];

    sprintf(sql,"select usr_id from user where usr_id = %d;", 
            *((int*)&user->buff[9]));
    if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    if (temp == 0) {
        mx_add_error_work_log(server_info, user, "NOT FOND USER!");
        return mx_create_response(user->buff[0], id_query, MQ_QS_NOT_FOUND);
    }
    free(temp);
    return 0;
}

static char *check_dialog_or_create_new_dialog(t_server *server_info,
                                               t_server_users *user) {
    char sql[1024];
    char *temp = 0;
    int id_query = *(int*)&user->buff[1];

    sprintf(sql,"select chat_id from chat where chat_name = '%d_%d' or "
            "chat_name = '%d_%d';", user->id_users, *((int*)&user->buff[9]),
            *((int*)&user->buff[9]), user->id_users);
    if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    if (temp != 0)
        return create_response_create_dialog(&temp, user->buff);
    sprintf(sql,"INSERT INTO chat values (NULL, '%d_%d', 1, %d, %d, "
            "datetime('now'));", user->id_users, *((int*)&user->buff[9]),
            user->id_users, *((int*)&user->buff[9]));
    if (mx_do_query(sql, 0, 0, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    return 0;
}

char *mx_create_dialog(t_server *server_info, t_server_users *user) {
    char sql[1024];
    char *temp = 0;

    temp = check_users(server_info, user);
    if (temp != 0)
        return temp;
    temp = check_dialog_or_create_new_dialog(server_info, user);
    if (temp != 0)
        return temp;
    sprintf(sql,"select MAX(chat_id) from chat where chat_id_creater = %d and"
            " chat_type = '1' and chat_id_user_dialog = %d;", user->id_users,
            *((int*)&user->buff[9]));
    if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    if (temp == 0)
        return mx_create_respons_error_and_log(server_info, user, "DON'T SEE "
            "NEW DIALOG!!!", MX_QS_ERR_SERV);
    return create_response_create_dialog(&temp, user->buff);
}
