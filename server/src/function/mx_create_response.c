#include "server.h"

char *mx_create_response(char id_request, int query, char status) {
    char *response = malloc(sizeof(char) * 10);

    response[0] = id_request;
    *(int*)&response[1] = query;
    *(int*)&response[5] = 10;
    response[9] = status;
    return response;
}

char *mx_create_respons_error_and_log(t_server *server_info,
    t_server_users *user, char *msg, char status) {
    char *response = malloc(sizeof(char) * 10);

    mx_add_error_work_log(server_info, user, msg);
    response[0] = user->buff[0];
    *((int*)&response[1]) = *((int*)&user->buff[1]);
    *((int*)&response[5]) = 10;
    response[9] = status;
    return response;
}
