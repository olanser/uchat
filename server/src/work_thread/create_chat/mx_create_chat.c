#include "server.h"
#include "defines.h"


// static bool check_name_chat(char *name, int len) {
//     int sum = len - 10;

//     if (name[sum] != 0)
//         return 0;
//     return 1;
// }

// static int create_response_create_chat(char **res, char *temp, void *request) {
//     int total_len = 20;
//     int len = strlen(temp);

//     *res = malloc(total_len);
//     memset(*res, 0, 20);
//     mx_memcpy(*res, request, 5);
//     *((int*)(&(*res)[5])) = total_len;
//     mx_memcpy(&(*res)[9], temp, len);
//     free(temp);
//     return total_len;
// }


// static int callback(void *data, int column, char **name, char **tabledata) {
//     *((char **)data) = mx_strdup(name[0]);
//     return 0;
// }



char *mx_create_chat(t_server *server_info, t_server_users *user) {
    // char sql[1024];
    // char *temp = 0;
    // char *response = NULL;

    // if (check_name_chat(&(user->buff)[9], *((int*)(&(user->buff)[5]))) == 0)
    //     mx_get_msg_response_10(MX_QS_ERR_FUNC, (user->buff), &response);
    // else {
    //     sprintf(sql,"INSERT INTO chat (chat_name, chat_id_creater,"
    //     " chat_time_creation) values"
    //     " ('%s', '%s', datetime('now'));", &(user->buff)[9], user->id_users);
    //     mx_do_query(sql, 0, 0, server_info);
    //     sprintf(sql,"select MAX(chat_id) from chat where"
    //     " chat_id_creater = '%s' and chat_type = '2';", user->id_users);
    //     mx_do_query(sql, callback, &temp, server_info);
    //     if (temp == 0)
    //         mx_get_msg_response_10(MX_QS_ERR_SERV, user->buff, &response);
    //     else 
    //         create_response_create_chat(&response, temp, user->buff);
    // }
    // return response;
    return 0;
}
