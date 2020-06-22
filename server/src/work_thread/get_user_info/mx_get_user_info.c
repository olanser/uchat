#include "server.h"
#include "defines.h"

// static int callback(void *data, int columns, char **name, char **tabledata) {
//     t_table_user *user =  malloc(sizeof(t_table_user));

//     user->first_name = mx_strdup(name[0]);
//     user->second_name = mx_strdup(name[1]);
//     user->nickname = mx_strdup(name[2]);
//     user->pass = mx_strdup(name[3]);
//     *((t_table_user**)data) = user;
//     return 0;
// }


// static int get_ok_msg(char **response, t_table_user *tuser) {
//     int i = 20;
//     int lens[3] = {mx_strlen(tuser->first_name), mx_strlen(tuser->second_name),
//         mx_strlen(tuser->nickname)};
//     int total_len = lens[0] + lens[1] + lens[2] + 23;

//     *response = malloc(total_len);
//     memset(*response, 0, total_len);
//     mx_memcpy(&(*response)[9], tuser->pass, strlen(tuser->pass));
//     mx_memcpy(&(*response)[i], tuser->first_name, lens[0] + 1);
//     i += mx_strlen(tuser->first_name) + 1;
//     mx_memcpy(&(*response)[i], tuser->second_name, lens[1] + 1);
//     i += mx_strlen(tuser->second_name) + 1;
//     mx_memcpy(&(*response)[i], tuser->nickname, lens[2] + 1);
//     return total_len;
// }

// /* return len of response */
// int mx_get_msg_user(char *request, t_table_user *tuser, char **response) {
//     int total_len =  get_ok_msg(response, tuser);

//     mx_memcpy(*response, request, 5);
//     //  (*response)[9] = (char)200;
//     *(int*)(&(*response)[5]) = total_len;
//     return total_len;
// }

char *mx_get_user_info(t_server *server_info, t_server_users *user) {
    return 0;
    // char sql[1024];
    // t_table_user *user = malloc(sizeof(t_table_user));;
    // int count;
    // char *response = NULL;
    // char *request = user->buff;

    // int status = 0;

    // if (mx_check_number(&request[9], 11) == 0) {
    //     response = mx_create_response(request[0], request[1], status);
    //     fprintf(MX_ERROR_THREAD, "not messege\n");
    //     response[9] = (char)100;
    //     return 10;
    // }
    // sprintf(sql,"select usr_frst_name, usr_scnd_name, usr_nickname, usr_id from user where usr_id = '%s';", &request[9]);
    // mx_do_query(sql,callback, &user, server_info);
    // if (user != 0) {
    //     count = mx_get_msg_user(request, user, response);
    //     mx_free_tuser(user);
    //     return NULL;
    // }
    // response = mx_create_response(request[0], request[1], status);
    // response[9] = (char)107;
    // return response;
}
