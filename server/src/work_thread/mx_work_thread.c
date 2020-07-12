#include "server.h"
#include "defines.h"

static bool check_request(t_server_users *user, t_server *server_info) {
    char *response = 0;

    if (user->id_users != 0) {
        if (user->buff[0] == 0 || user->buff[0] == 1) {
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_LOG_MANY);
        }
        else
            return true;
    }
    else {
        if (user->buff[0] == 0 || user->buff[0] == 1)
            return true;
        else
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_RIGHT);
    }
    mx_write_socket(user, response);
    free(response);
    return false;
}

static bool check_size(t_server_users *user, t_server *server_info) {
    const int min_size[23] = {313, 211, 16, 20, 17, 0, 13, 0, 29, 11, 13, 0,
                              21, 0, 0, 13, 0, 9, 10, 9, 17, 255, 25};
    const int max_size[23] = {313, 211, 1024, 1024, 17, 0, 13, 0, 29, 1024,
                              13, 0, 21, 0, 0, 13, 0, 9, 10, 9, 10000, 10000,
                              10000};
    char *response = 0;
    char log[75];

    if (*((int*)&user->buff[5]) < min_size[user->buff[0]]
        || *((int*)&user->buff[5]) > max_size[user->buff[0]]) {
        response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_FUNC);
    }
    else
        return true;
    sprintf(log, "ERROR size query!! work ID user = %d, API = %d, SIZE = "
            "%d\n", user->id_users, user->buff[0], *((int*)&user->buff[5]));
    mx_add_log(server_info, log);
    mx_write_socket(user, response);
    free(response);
    return false;
}

void mx_work_thread(t_server *server_info, t_server_users *user) {
    char comand = user->buff[0];
    int size = *((int*)&(user->buff[5]));
    char *response;
    char log[75];

    sprintf(log, "Start work ID user = %d, API = %d\n", user->id_users,
            user->buff[0]);
    mx_add_log(server_info, log);
    if (check_request(user, server_info) && check_size(user, server_info)) {
        response = mx_do_request(server_info, user);
        if (response) {
            mx_write_socket(user, response);
            free(response);
        }
   }
    sprintf(log, "FINISH work ID user = %d, API = %d\n", user->id_users,
            user->buff[0]);
    mx_add_log(server_info, log);
}
