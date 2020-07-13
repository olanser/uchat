#include "server.h"
#include "defines.h"

static void build_req(char **response, char *request, t_server_users *user,
                      unsigned int seconds) {
    *response = (char *)malloc(17);
    *response[0] = request[0];
    *((int*)&(*response)[1]) = *(int*)&request[1];
    *((int*)&(*response)[5]) = 17;
    *((int *)&(*response)[9]) = user->id_users;
    *((int *)&(*response)[13]) = seconds;
}

char *mx_create_unique_name(t_server *server_info, t_server_users *user) {
    char *response = NULL;
    char *request = user->buff;
    time_t seconds;
    unsigned int secs;

    time(&seconds);
    secs = (unsigned int) seconds;
    build_req(&response, request, user, secs);
    return response;
}
