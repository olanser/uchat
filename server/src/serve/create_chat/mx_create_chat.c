#include "header.h"

static bool check_name_chat(char *name, int len) {
    int sum = len - 10;

    if (name[sum] != 0)
        return 0;
    return 1;
}

static int create_response_create_chat(char **response, char *temp, void *request) {
    int total_len = 20;
    int len = strlen(temp);

    *response = malloc(total_len);
    memset(*response, 0, 20);
    mx_memcpy(*response, request, 5);
    *(int*)(&(*response)[5]) = total_len;
    mx_memcpy(&(*response)[9], temp, len);
    free(temp);
    return total_len;
}


static int callback(void *data, int columns, char **name, char **tabledata) {
    *((char **)data) = mx_strdup(name[0]);
    return 0;
}

int mx_create_chat(void *request, char **response, t_user *user_info) {
    char sql[1024];
    char *temp = 0;

    if (check_name_chat(&request[9], *(int*)(&request[5])) == 0)
        return mx_get_msg_response_10(MX_QS_ERR_FUNC, request, response);
    sprintf(sql,"INSERT INTO chat (chat_name, chat_id_creater, chat_time_creation) values ('%s', '%s', datetime('now'));", &request[9], user_info->id);
    mx_do_query(sql, 0, 0);
    sprintf(sql,"select MAX(chat_id) from chat where chat_id_creater = '%s' and chat_type = '2';", user_info->id);
    mx_do_query(sql, callback, &temp);
    printf("%s\n", temp);
    if (temp == 0)
        return mx_get_msg_response_10(MX_QS_ERR_SERV, request, response);
    return create_response_create_chat(response, temp, request);
}  