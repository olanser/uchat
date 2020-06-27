#include "server.h"
#include "defines.h"


static int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

static void spint_one(char *request, char *sql, t_server_users *user) {
    sprintf(sql,"select cou_id from cou LEFT JOIN chat where"
        " cou_char_id = '%s' and cou_usr_id = '%s'"
        " and chat_type = 2 and chat_id = %s;",
         &request[9], user->id_users, &request[9]);
}

static void spint_two(char *request, char *sql, t_server_users *user) {
    sprintf(sql,"delete from cou where"
        " cou_char_id = '%s' and cou_usr_id = '%s';",
            &request[9], user->id_users);
}

char *mx_leave_chat(t_server *server_info, t_server_users *user) {
    char sql[1024];
    int check = 0;
    char *res = NULL;

    if (mx_check_number(&(user->buff)[9], 11) == 0)
        mx_get_msg_response_10(MX_QS_ERR_FUNC, user->buff, &res);
    else {
        spint_one(user->buff, sql, user);
        mx_do_query(sql, callback, &check, server_info);
        if (check == 0)
            mx_get_msg_response_10(MQ_QS_NOT_FOUND, user->buff, &res);
        else {
            spint_two(user->buff, sql, user);
            if (mx_do_query(sql, 0, 0, server_info))
                mx_get_msg_response_10(MX_QS_ERR_REQUEST, user->buff, &res);
            else
                mx_get_msg_response_10((char)MX_QS_OK, user->buff, &res);
        }
    }
    return res;
}

