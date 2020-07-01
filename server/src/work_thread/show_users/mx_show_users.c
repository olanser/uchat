#include "server.h"


static int count_response_len(t_user_in_chat *list) {
    int len = 10;

    while (list) {
        len = len + 105;
        list = list->next;
    }
    return len;
}

static int callback_one(void *data, int column, char **tdata, char **name) {
    mx_push_char_users((t_user_in_chat **)data, tdata[0], tdata[1]);
    return 0;
}

static void build_answer(t_user_in_chat *find, char **response,
                        char *req) {
    t_user_in_chat *list = find;

    int counter = 10;
    int size = count_response_len(find);
    *response = (char *)malloc(size);
    memset(*response, 0, size);
    *response[0] = req[0];
    *((int*)&((*response)[1])) = *((int *)&req[1]);
    *((int*)&((*response)[5])) = size;
    (*response)[9] = (char)200;
    while (list) {
        *(int*)&(*response)[counter] = list->usr_id;
        counter = counter + 4;
        mx_memcpy(&((*response)[counter]), list->usr_nickname, 
                    strlen(list->usr_nickname));
        counter = counter + 101;
        list = list->next;
    }
}

char *mx_show_users(t_server *server_info, t_server_users *user) {
    char sql[1024];
    char *request = user->buff;
    t_user_in_chat *find_users = NULL;
    char *response = NULL;

    sprintf(sql, "select usr_id, usr_nickname from user where usr_nickname"
                " like '%s\%\%' LIMIT 10;", &request[9]);
    
    mx_do_query(sql, callback_one, &find_users, server_info);
    build_answer(find_users, &response, request);
    mx_delete_chat_users(&find_users);
    return response;
}
