#include "server.h"
#include "defines.h"

static int callback(void *param, int column, char **data, char **names) {
    char *response = malloc(sizeof(char) * 115);

    memset(response, 0, 115);
    response[0] = 10;
    response[5] = 115;
    if (data[1][0] == '2')
        response[9] = '2';
    else
        response[9] = '1';
    *((int*)&response[10]) = atoi(data[2]);
    sprintf(&response[14], "%s", data[0]);
    mx_push_back(param, response);
    return 0;
}

static void write_server(t_list **list, t_server_users *user) {

    while(*list) {
        mx_write_socket(user, (*list)->data);
        mx_pop_front_free_data(list);
    }
}

char *mx_get_chats_info(t_server *server_info, t_server_users *user) {
    char sql[130];
    t_list *list = 0;

    sprintf(sql, "select chat_name, chat_type, chat_id from chat where chat_id "
            "in (select cou_chat_id from cou where cou_usr_id = %d);",
            user->id_users);
    if (mx_do_query(sql, callback, &list, server_info) != SQLITE_OK) {
        write_server(&list, user);
        return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
                                  MQ_QS_ERR_SQL);
    }
    write_server(&list, user);
    return 0;
}
