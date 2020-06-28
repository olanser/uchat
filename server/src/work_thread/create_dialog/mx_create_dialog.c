#include "server.h"
#include "defines.h"


// static char *create_response_create_dialog(char **temp, char *request) {
//     int total_len = 31;
//     char *respons = malloc(total_len);

//     memset(respons, 0, 31);
//     mx_memcpy(respons, request, 5);
//     *(int*)(&(respons)[5]) = total_len;
//     sprintf(&(respons)[9], "%s", *temp);
//     sprintf(&(respons)[20], "%s", &request[9]);
//     free(*temp);
//     return respons;
// }

// static char *check_users_and_dialog(t_server *server_info,
//                                     t_server_users *user) {
//     char sql[1024];
//     char *temp = 0;
//     int id_query = *(int*)&user->buff[1];

//     sprintf(sql,"select usr_id from user where usr_id = %s;", &user->buff[9]);
//     if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
//         return mx_create_response(user->buff[0], id_query, MQ_QS_ERR_SQL);
//     if (temp == 0)
//         return mx_create_response(user->buff[0], id_query, MQ_QS_NOT_FOUND);
//     free(temp);
//     temp = 0;
//     sprintf(sql,"select chat_id from chat where chat_name = '%s_%s' or "
//             "chat_name = '%s_%s';", user->id_users, &user->buff[9],
//             &user->buff[9], user->id_users);
//     if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
//         return mx_create_response(user->buff[0], id_query, MQ_QS_ERR_SQL);
//     if (temp != 0)
//         return create_response_create_dialog(&temp, user->buff);
//     return 0;
// }

// static char *create_new_dialog(t_server *server_info, t_server_users *user) {
//     char sql[1024];

//     sprintf(sql,"INSERT INTO chat values (NULL, '%s_%s', 1, '%s', '%s', "
//             "datetime('now'));", user->id_users, &user->buff[9], user->id_users,
//             &user->buff[9]);
//     if (mx_do_query(sql, 0, 0, server_info) != SQLITE_OK)
//         return mx_create_response(user->buff[0], *((int*)&user->buff[1]),
//                                   MQ_QS_ERR_SQL);
//     return 0;
// }

char *mx_create_dialog(t_server *server_info, t_server_users *user) {
    // char sql[1024];
    // char *temp = 0;
    // int id_query = *((int*)&user->buff[1]);

    // if (mx_check_number(&user->buff[9], 11) == 0)
    //     return mx_create_response(user->buff[0], id_query, MX_QS_ERR_FUNC);
    // temp = check_users_and_dialog(server_info, user);
    // if (temp != 0)
    //     return temp;
    // temp = create_new_dialog(server_info, user);
    // if (temp != 0)
    //     return temp;
    // sprintf(sql,"select MAX(chat_id) from chat where chat_id_creater = '%s' and"
    //         " chat_type = '1' and chat_id_user_dialog = '%s';", user->id_users,
    //         &user->buff[9]);
    // if (mx_do_query(sql, mx_return_one_str, &temp, server_info) != SQLITE_OK)
    //     return mx_create_response(user->buff[0], id_query, MQ_QS_ERR_SQL);
    // if (temp == 0)
    //     return mx_create_response(user->buff[0], id_query, MX_QS_ERR_SERV);
    // return create_response_create_dialog(&temp, user->buff);
    return 0;
}
