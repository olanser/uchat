#include "header.h"

static bool check_name_chat(char *name, int len) {
    int sum = len - 10;

    if (name[sum] != 0)
        return 0;
    return 1;
}

static int create_response_create_dialog(char **response, char *temp, void *request) {
    int total_len = 31;
    int len = strlen(temp);

    *response = malloc(total_len);
    memset(*response, 0, 31);
    mx_memcpy(*response, request, 5);
    *(int*)(&(*response)[5]) = total_len;
    mx_memcpy(&(*response)[9], temp, len);
    mx_memcpy(&(*response)[20], &((char*)request)[9], strlen(&((char*)request)[9]));
    free(temp);
    return total_len;
}


static int callback(void *data, int columns, char **name, char **tabledata) {
    *((char **)data) = mx_strdup(name[0]);
    return 0;
}

int mx_create_dialog(void *request, char **response, t_user *user_info) {
    char sql[1024];
    char *temp = 0;

    if (mx_check_number(&request[9], 11) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        return mx_get_msg_response_10(MX_QS_ERR_FUNC, request, response);;
    }
    sprintf(sql,"select usr_id from user where usr_id = %s;", &request[9]);
    mx_do_query(sql, callback, &temp);
    if (temp == 0)
        return mx_get_msg_response_10(MQ_QS_NOT_FOUND, request, response);
    free(temp);
    temp = 0;
    sprintf(sql,"select chat_id from chat where chat_name = '%s_%s' or chat_name = '%s_%s';", user_info->id, &request[9], &request[9], user_info->id);
    mx_do_query(sql, callback, &temp);
    if (temp != 0)
        return create_response_create_dialog(response, temp, request);
    sprintf(sql,"INSERT INTO chat values (NULL, '%s_%s', 1, '%s', '%s', datetime('now'));", user_info->id, &request[9], user_info->id, &request[9]);
    mx_do_query(sql, 0, 0);
    sprintf(sql,"select MAX(chat_id) from chat where chat_id_creater = '%s' and chat_type = '1' and chat_id_user_dialog = '%s';", user_info->id, &request[9]);
    mx_do_query(sql, callback, &temp);
    if (temp == 0)
        return mx_get_msg_response_10(MX_QS_ERR_SERV, request, response);
    return create_response_create_dialog(response, temp, request);
}
