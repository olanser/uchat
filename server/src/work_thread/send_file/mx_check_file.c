#include "server.h"
#include "defines.h"

static char *get_unique_name(char *request, t_server_users *user) {
    int user_req_id = *((int *)&request[275]);
    char *first_part;
    char *second_part;
    char *unique_name;

    if (user->id_users != user_req_id)
        return NULL;
    else {
        first_part = mx_itoa(user_req_id);
        second_part = mx_itoa(*((int *)&request[279]));
        unique_name = mx_strjoin3(first_part, second_part);
        return unique_name;
    }
}

int mx_check_file(t_file_message *message, t_server_users *user) {
    int len = 0;
    char *request = user->buff;

    message->unique_name = NULL;
    message->id_query = &request[1];
    message->unique_name = get_unique_name(request, user);
    if (message->unique_name == NULL)
        return 1;
    message->id_chat = *(int *)(&request[14]);
    message->true_name = &((char *)request)[19];
    message->size = *(int *)(&request[10]);
    message->file_type = request[9];
    message->avatar = request[284];
    return 0;
}