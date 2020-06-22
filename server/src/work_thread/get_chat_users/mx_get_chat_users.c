#include "server.h"
#include "defines.h"

// static int callback_one(void *data, int columns, char **name, char **tabledata) {
//     for (int i = 0; i < columns; i++){
//         if (i % 2 == 0) {
//             mx_push_char_users((t_user_in_chat **)data, name[i], name[i+1]);    
//         }
//     }
//     return 0;
// }


// static int count_response_len(t_user_in_chat *list) {
//     int len = 20;

//     while (list) {
//         len = len + 62;
//         list = list->next;
//     }
//     return len;
// }

// static void build_res(t_user_in_chat *list, char **response, int len, 
//                         void *req) {
//     *response = malloc(sizeof(char) * len);
//     int pointer = 20;

//     memset(*response, 0, sizeof(char)*len);
//     (*response)[0] = 7;
//     mx_memcpy(&(*response)[1], &((char *)req)[1], 4);
//     *(int*)(&(*response)[5]) = len;
//     mx_memcpy(&(*response)[9], &req[9], 11);
//     while (list) {
//         mx_memcpy(&(*response)[pointer], list->usr_id, strlen(list->usr_id));
//         pointer = pointer + 11;
//         mx_memcpy(&(*response)[pointer], list->usr_nickname, 
//                     strlen(list->usr_nickname));
//         pointer = pointer + 51;
//         list = list->next;
//     }
// }

// static void build_answer(t_server *server_info, t_server_users *user) {
//     char sql[200];

//     sprintf(sql, "SELECT usr_id, usr_nickname from user where usr_id IN (SELECT cou_usr_id from cou where cou_char_id=%s);", chat_id);
//     mx_do_query(sql, callback_one, list);
// }

char *mx_get_chat_users(t_server *server_info, t_server_users *user) {
    return 0;
    // t_user_in_chat *list = NULL;
    // int res_len = 10;

    // char *response = NULL;
    // char *request = user->buff;

    // int status = 0;

    // if(mx_check_user_in_char(&(request[9]), user->id_users)) {
    //     build_answer(&(request[9]), &list);
    //     res_len = count_response_len(list);
    //     build_res(list, &response, res_len, request);
    //     mx_delete_chat_users(&list);
    // }
    // else {
    //     response = mx_create_response(request[0], request[1], status);
    //     fprintf(MX_ERROR_THREAD, "permission\n");
    // }
    // return response;
}



