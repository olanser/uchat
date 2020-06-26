#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

int mx_leave_chat(void *request, char **response, t_user *user_info) {
    char sql[1024];
    int check = 0;

    if (mx_check_number(&request[9], 11) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        return mx_get_msg_response_10(MX_QS_ERR_FUNC, request, response);
    }
    sprintf(sql,"select cou_id from cou LEFT JOIN chat where cou_char_id = '%s' and cou_usr_id = '%s' and chat_type = 2 and chat_id = %s;", &request[9], user_info->id, &request[9]);
    mx_do_query(sql, callback, &check);
    if (check == 0)
        return mx_get_msg_response_10(MQ_QS_NOT_FOUND, request, response);
    sprintf(sql,"delete from cou where cou_char_id = '%s' and cou_usr_id = '%s';", &request[9], user_info->id);
    if (mx_do_query(sql, 0, 0))
        return mx_get_msg_response_10(MX_QS_ERR_REQUEST, request, response);
    return mx_get_msg_response_10((char)MX_QS_OK, request, response);
}   