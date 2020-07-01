#include "server.h"
#include "defines.h"

#include <sys/stat.h>


static char *get_unique_name(char *request, t_server_users *user) {
    int user_req_id = *((int *)&request[76]);

    printf("uniq user_id == %d\n");

    if (user->id_users != user_req_id)
        return NULL;
    else
    {
        char *first_part = mx_itoa(user_req_id);
        char *second_part = mx_itoa(*((int *)&request[80]));
        char *unique_name = mx_strjoin3(first_part, second_part);

        return unique_name;
    }
}

int mx_check_file(char *request, t_file_message *message,
                    t_server_users *user) {
    int len = 0;

    message->unique_name = NULL;
    message->id_query = &request[1];
    if (mx_check_number(&request[14], 11) == 0)
        return 1;
    printf("uniq\n");
    message->unique_name = get_unique_name(request, user);
    if (message->unique_name == NULL)
        return 1;
    message->id_chat = &request[14];
    message->true_name = &((char *)request)[26];
    message->size = *(int *)(&request[10]);
    message->file_type = request[9];
    printf("check file end\n");
    return 0;

}

static void create_sql_request(t_file_message message, t_server_users *user, char *buf) {

    sprintf(buf, "INSERT INTO msg (msg_creator, msg_send_time, msg_file_type, msg_chat_id, msg_file_size, msg_status, msg_file_name) VALUES (%d, datetime('now'), %d, %s, %d, %s, '%s');", user->id_users, message.file_type, message.id_chat, message.size, "5", message.true_name);

}

static int callback_one(void *data, int col, char **name, char **tabledata) {
    *(char **)data = strdup(name[0]);
    return 0;
}

// //{21}{id_of_query(4)}{size(4)}{file_type(1)}{size_of_file(4)){id chat(10)}\0{name(50)}\0{unique_name(?)}\0

//{5}{id_of_query(4)}{size_of_head(4)}{file_type(1)}{size_of_file(4)){triger end of file(1)}{id chat(10)}\0{name(50)}\0{unique_name(11)}{data(...)} 

// int mx_send_file(void *request, char **response, t_user *user_info) {
//     t_file_message message;
//     char sql_request[500];
//     char name[100];

//     mx_create_response(request, response);
//     if (mx_check_file(((char*)request), &message) == 0) {
//         fprintf(MX_ERROR_THREAD, "not messege\n");
//         (*response)[9] = (char)100;
//         return 10;
//     }
//     if (mx_check_user_in_char(message.id_chat, user_info->id) == 0) {
//         fprintf(MX_ERROR_THREAD, "permission\n");
//         (*response)[9] = (char)103;
//         return 10;
//     }
//     create_sql_request(message, user_info, sql_request);
//     if (save_file(request, user_info, &message) == 0) {
//         if (mx_do_query(sql_request,0,0) == 0) {
//             (*response)[9] = (char)200;
//             sprintf(sql_request, "SELECT msg_id from msg where msg_creator = '%s' ORDER by msg_id DESC LIMIT 1;", user_info->id);
//             mx_do_query(sql_request, callback_one, &(message.id_message));
//             sprintf(sql_request, "download/%s", message.buf_name);
//             sprintf(name, "download/%s", message.id_message);
//             rename(sql_request, name);
//             mx_create_signal_new_message(message.id_chat);
//             return 10;
//         }
    
//     }

char *mx_end_of_file(t_server *server_info, t_server_users *user) {
    t_file_message message;
    char sql_request[500];
    char *response = NULL;
    char *request = user->buff;
    char name[100];

    user->id_users = 1;
    printf("start\n");

    if (mx_check_file(request, &message, user) == 1) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        response = mx_create_response(request[0], *(int *)(&request[1]), (char)103);
    }
    else {
        printf("in req\n");
        create_sql_request(message, user, sql_request);
        mx_do_query(sql_request,0,0, server_info);
        sprintf(sql_request, "SELECT msg_id from msg where msg_creator = '%d' ORDER by msg_id DESC LIMIT 1;", user->id_users);
        mx_do_query(sql_request, callback_one, &(message.id_message), server_info);
        sprintf(sql_request, "download/%s", message.unique_name);
        sprintf(name, "download/%s", message.id_message);
        rename(sql_request, name);

    }

    return response;
}
