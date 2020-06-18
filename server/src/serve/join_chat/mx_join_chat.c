#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

static bool mx_check_permission_in_char(char *id_chat) {
    char sql[85];

    int check = 0;
    sprintf(sql, "SELECT chat_type FROM chat where chat_id = %s and chat_type= '2';", id_chat);
    if (mx_do_query(sql, callback, &check) == 0) {
        if (check != 0) {
            return 1;
        }
    }
    return 0;
}

int mx_join_chat(void *request, char **response, t_user *user_info) {
    char sql[1024];

    if (mx_check_number(&request[9], 11) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        return mx_get_msg_response_10(MX_QS_ERR_FUNC, request, response);;
    }
    if (mx_check_permission_in_char(&request[9]) == 0) {
        fprintf(MX_ERROR_THREAD, "permission\n");
        return mx_get_msg_response_10(MX_QS_ERR_RIGHT, request, response);
    }
    if (mx_check_user_in_char(&request[9], user_info->id))
       return mx_get_msg_response_10((char)MX_QS_OK, request, response);
    sprintf(sql, "insert into cou (cou_char_id, cou_usr_id) values ('%s', '%s');", &request[9], user_info->id);
    mx_do_query(sql, callback, 0);
    return mx_get_msg_response_10((char)MX_QS_OK, request, response);
}
