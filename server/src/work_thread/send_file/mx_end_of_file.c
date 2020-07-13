#include "server.h"
#include "defines.h"
#include <sys/stat.h>

static char *check_query(t_server *server_info, t_server_users *user) {
    int query = *((int*)&user->buff[1]);
    char log[1024];

    if (mx_check_user_in_chat(*((int*)&user->buff[14]), user->id_users,
                              server_info) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_DONT_HAVE_CHAT_USER, MX_QS_ERR_RIGHT);
    return 0;
}

static int callback(void *data, int column, char **name, char **tabledata) {
    int sum = 307;
    char *response =  malloc(sizeof(char) * sum);

    memset(response, 0, sum);
    response[0] = 2;
    *((int*)&response[5]) = sum;
    *((int*)&response[9]) = atoi(name[0]);
    *((int*)&response[13]) = atoi(name[1]);
    *((int*)&response[17]) = atoi(name[2]);
    sprintf(&response[21], "%s",name[3]);
    response[41] = name[4][0];
    *((int*)&response[42]) = atoi(name[5]);
    sprintf(&response[46], "%s",name[6]);
    response[302] = atoi(name[7]);
    *((int*)&response[303]) = atoi(name[8]);
    *(char**)data = response;
    return 0;
}

static char *create_response_to_users(t_server *server_info, 
                            t_server_users *user, t_file_message message) {
    char *respons = 0;
    char sql[1024];

    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_avatar, msg_type, msg_file_name, msg_file_type, "
            "msg_file_size from msg where msg_creator = %d and msg_status = 5"
            " and msg_chat_id = %d and msg_file_name = '%s' ORDER by msg_id "
            "DESC LIMIT 1;", user->id_users, message.id_chat,
            message.true_name);
    mx_do_query(sql, callback, &respons, server_info);
    return respons;
}

char *mx_end_of_file(t_server *server_info, t_server_users *user) {
    t_file_message message;
    char sql_request[1024];
    char *response = check_query(server_info, user);

    if (response)
        return response;
    if (mx_check_file(&message, user) == 1)
        return mx_create_respons_error_and_log(server_info, user, 
            "not messege\n", MX_QS_ERR_RIGHT);
    else {
        mx_creat_msg_to_database_and_rename_file(server_info, user, &message);
        response = create_response_to_users(server_info, user, message);
        if (response) {
            sprintf(sql_request, "select cou_usr_id from cou where "
                    "cou_chat_id = %d;", message.id_chat);
            mx_send_response_user(server_info, response, sql_request);
            free(response);
        }
    }
    return NULL;
}
