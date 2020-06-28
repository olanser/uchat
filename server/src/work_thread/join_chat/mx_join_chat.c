#include "server.h"
#include "defines.h"


// static int callback(void *data, int columns, char **name, char **tabledata) {
//     *((int*)data) += 1;
//     return 0;
// }

// static bool mx_check_permission_in_char(char *id_chat, t_server *server_info) {
//     char sql[85];

//     int check = 0;
//     sprintf(sql, "SELECT chat_type FROM chat where chat_id = %s"
//                 " and chat_type= '2';", id_chat);
//     if (mx_do_query(sql, callback, &check, server_info) == 0) {
//         if (check != 0) {
//             return 1;
//         }
//     }
//     return 0;
// }


// bool mx_check_user_in_char(char *id_chat, char *id_user,
//                             t_server *server_info) {
//     char sql[85];

//     int check = 0;
//     sprintf(sql, "SELECT * FROM cou where cou_char_id = %s AND"
//                 " cou_usr_id = %s;", id_chat, id_user);
//     if (mx_do_query(sql, callback, &check, server_info) == 0) {
//         if (check != 0) {
//             return 1;
//         }
//     }
//     return 0;
// }


// void mx_get_msg_response_10(char status, char *request, char **response) {
//     int total_len = 10;

//     *response = malloc(total_len);
//     mx_memcpy(*response, request, 5);
//     (*response)[9] = status;
//     *(int*)(&(*response)[5]) = total_len;
// }

char *mx_join_chat(t_server *server_info, t_server_users *user) {
    // char sql[1024];
    // char *request = user->buff;
    // char *response = NULL;

    // if (mx_check_number(&request[9], 11) == 0)
    //     mx_get_msg_response_10(MX_QS_ERR_FUNC, request, &response);
    // else if (mx_check_permission_in_char(&request[9], server_info) == 0) {
    //     fprintf(MX_ERROR_THREAD, "permission\n");
    //     mx_get_msg_response_10(MX_QS_ERR_RIGHT, request, &response);
    // }
    // else if (mx_check_user_in_char(&request[9], user->id_users, server_info))
    //    mx_get_msg_response_10((char)MX_QS_OK, request, &response);
    // else {
    //     sprintf(sql, "insert into cou (cou_char_id, cou_usr_id) values"
    //             " ('%s', '%s');", &request[9], user->id_users);
    //     mx_do_query(sql, callback, 0, server_info);
    //     mx_get_msg_response_10((char)MX_QS_OK, request, &response);
    // }
    // return response;
    return 0;
}
