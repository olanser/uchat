#include "server.h"
#include "defines.h"

static bool check_request(t_server_users *user) {
    char *response = 0;

    if (user->id_users) {
        if (user->buff[0] == 0 || user->buff[0] == 1 || user->buff[0] == 12) {
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_LOG_MANY);
        }
        else
            return true;
    }
    else {
        if (user->buff[0] == 0 || user->buff[0] == 1 || user->buff[0] == 12) {
            return true;
        }
        else {
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_RIGHT);
        }
    }
    mx_write_socket(user, response);
    free(response);
    return false;
}

static bool check_size(t_server_users *user) {
    const int min_size[19] = {313, 211, 22, 33, 31, 20, 20, 20, 29, 11, 20, 20,
                              0, 20, 110, 20, 20, 9};
    const int max_size[19] = {313, 211, 1024, 1024, 31, 1024, 20, 20, 29, 1024,
                              20, 1024, 0, 20, 110, 20, 20, 9};
    char *response = 0;

    if (*((int*)&user->buff[5]) < min_size[user->buff[0]]
        || *((int*)&user->buff[5]) > max_size[user->buff[0]]) {
        response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_FUNC);
    }
    else
        return true;
    printf("ERROR size query!!!!\n");
    mx_write_socket(user, response);
    free(response);
    return false;
}

void mx_work_thread(t_server *server_info, t_server_users *user) {
    char comand = user->buff[0];
    int size = *((int*)&(user->buff[5]));
    char *response;

    printf("in do req -- %d\n", user->buff[0]);
    if (check_request(user) && check_size(user)) {
        response = mx_do_request(server_info, user);
        if (response) {
            mx_write_socket(user, response);
            free(response);
        }
    }
}
