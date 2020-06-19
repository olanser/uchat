#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    t_user *user_info = (t_user *)((void**)data)[0];
    int i = -1;
    char *temp;

    if (name[1][0] == '2') {
        *((char**)((void**)data)[1]) = mx_strdup(name[0]);
        *((char**)((void**)data)[2]) = "2";
    }
    else {
        *((char**)((void**)data)[2]) = "1";
        temp = mx_strnew(11);
        while (name[0][++i] != 0 && user_info->id[i] != 0 && name[0][i] == user_info->id[i]);
        if (i == 0) {
            for (;name[0][i] != '_'; i++)
                temp[i] = name[0][i];
        }
        else if (name[0][i] == '_') {
            for (int t = 0; name[0][++i] != 0; t++)
                temp[t] = name[0][i];
        }
        *((char**)((void**)data)[1]) = temp;
    }
    return 0;
}

int mx_get_chat_info(void *request, char **response, t_user *user_info) {
    char sql[1024];
    char *temp = 0;
    char *type = 0;
    void *call[3] = {user_info, &temp, &type};

    if (mx_check_number(&request[9], 11) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        return mx_get_msg_chat(MX_QS_ERR_FUNC, request, 0, response);;
    }
    if (mx_check_user_in_char(&request[9], user_info->id) == 0) {
        fprintf(MX_ERROR_THREAD, "permission\n");
        return mx_get_msg_chat(MX_QS_ERR_RIGHT, request, 0, response);
    }
    sprintf(sql, "select chat_name, chat_type from chat where chat_id = '%s';", &request[9]);
    mx_do_query(sql, callback, call);
    return mx_get_msg_chat((char)MX_QS_OK, request, call, response);
}
