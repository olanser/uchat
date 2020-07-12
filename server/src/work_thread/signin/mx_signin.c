#include "server.h"
#include "defines.h"

static int read_request(char *request, t_table_user *tuser) {
    tuser->nickname = mx_strdup(&request[9]);
    tuser->pass = mx_strdup(&request[110]);
    return 0;
}

static void mx_free_tuser(t_table_user *tuser) {
    free(tuser->first_name);
    free(tuser->second_name);
    free(tuser->nickname);
    free(tuser->pass);
}

static t_table_user* get_tuser() {
    t_table_user *tuser = malloc(sizeof(t_table_user));

    tuser->first_name = 0;
    tuser->second_name = 0;
    tuser->nickname = 0;
    tuser->pass = 0;
    return tuser;
}

char *mx_signin(t_server *server_info, t_server_users *user) {
    t_table_user *tuser = get_tuser();
    char status = 0;
    char *response = 0;

    read_request(user->buff, tuser);
    status = mx_login_check_user(tuser, server_info, user);
    mx_get_msg_login(status, user->buff, tuser, &response);
    mx_free_tuser(tuser);
    free(tuser);
    return response;
}
