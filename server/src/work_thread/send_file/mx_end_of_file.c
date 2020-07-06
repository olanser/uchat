#include "server.h"
#include "defines.h"

#include <sys/stat.h>


static char *get_unique_name(char *request, t_server_users *user) {
    int user_req_id = *((int *)&request[275]);

    printf("uniq user_id == %d\n", user_req_id);
    printf("sec == %d\n", *((int *)&request[279]));//+255

    printf("tru name - %s\n", &request[19]);

    if (user->id_users != user_req_id)
        return NULL;
    else
    {
        char *first_part = mx_itoa(user_req_id);
        char *second_part = mx_itoa(*((int *)&request[279]));
        char *unique_name = mx_strjoin3(first_part, second_part);

        return unique_name;
    }
}

int mx_check_file(char *request, t_file_message *message,
                    t_server_users *user) {
    int len = 0;

    message->unique_name = NULL;
    message->id_query = &request[1];
    printf("uniq\n");
    message->unique_name = get_unique_name(request, user);
    if (message->unique_name == NULL)
        return 1;
    message->id_chat = *(int *)(&request[14]);

    message->true_name = &((char *)request)[19]; //19
    message->size = *(int *)(&request[10]);
    message->file_type = request[9];
    message->avatar = request[284];//+255

    printf("avatar = %d\n", request[284]);

    printf("check file end\n");
    return 0;

}

static void create_sql_request(t_file_message message, t_server_users *user, char *buf) {

    sprintf(buf, "INSERT INTO msg (msg_creator, msg_send_time, msg_file_type, msg_chat_id, msg_file_size, msg_status, msg_file_name, msg_avatar, msg_type) VALUES (%d, datetime('now'), %d, %d, %d, %s, '%s', %d, %d);", user->id_users, message.file_type, message.id_chat, message.size, "5", message.true_name, message.avatar, 3);

}

static int callback_one(void *data, int col, char **name, char **tabledata) {
    *(char **)data = strdup(name[0]);
    return 0;
}


static char *check_query(t_server *server_info, t_server_users *user) {
    int query = *((int*)&user->buff[1]);
    char log[1024];


    // if (mx_check_avatar(user->buff[80]) == 0)
    //     return mx_create_respons_error_and_log(server_info, user,
    //         MX_EROR_ID_AVATAR, MX_QS_ERR_FUNC);
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
    sprintf(&response[41], "%s",name[4]);
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

    printf("in create\n");

    sprintf(sql, "select msg_id, msg_chat_id, msg_creator, msg_send_time, "
            "msg_avatar, msg_type, msg_file_name, msg_file_type, msg_file_size from msg where msg_creator = "
            "%d and msg_status = 5 and msg_chat_id = %d and "
            "msg_file_name = '%s' ORDER by msg_id DESC LIMIT 1;",
            user->id_users, message.id_chat, message.true_name);
    printf("in middle\n");
    // printf("msg_true_name = %s\n", message.true_name);
    mx_do_query(sql, callback, &respons, server_info);

    printf("end\n");
    printf("RESPONSE1 - %s\n", respons);

    return respons;
}

char *mx_end_of_file(t_server *server_info, t_server_users *user) {
    //user->id_users = 1; //!!!!!!!!!!!!!!!!!

    t_file_message message;
    char sql_request[1024];
    char *response = check_query(server_info, user);
    char *request = user->buff;
    char name[256];

    if (response) {
        return response;
    }
    if (mx_check_file(request, &message, user) == 1) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        response = mx_create_response(request[0], *(int *)(&request[1]), (char)103);
    }
    else {
        create_sql_request(message, user, sql_request);
        mx_do_query(sql_request,0,0, server_info);
        sprintf(sql_request, "SELECT msg_id from msg where msg_creator = '%d' ORDER by msg_id DESC LIMIT 1;", user->id_users);
        mx_do_query(sql_request, callback_one, &(message.id_message), server_info);
        sprintf(sql_request, "download/%s", message.unique_name);
        sprintf(name, "download/%s", message.id_message);
        rename(sql_request, name);
        free(message.unique_name);
        free(message.id_message);
        response = create_response_to_users(server_info, user, message);
        if (response) {
            sprintf(sql_request, "select cou_usr_id from cou where cou_chat_id = "
                    "%d;", message.id_chat);
            mx_send_response_user(server_info, response, sql_request);
            free(response);
        }
    }

    return NULL;
}
