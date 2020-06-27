#include "server.h"
#include "defines.h"

static void mx_free_tuser(t_table_user *tuser) {
    free(tuser->first_name);
    free(tuser->second_name);
    free(tuser->nickname);
    free(tuser->id);
    free(tuser);
}

static int callback(void *data, int columns, char **name, char **tabledata) {
    t_table_user *user =  malloc(sizeof(t_table_user));
   
    user->first_name = mx_strdup(name[0]);
    user->second_name = mx_strdup(name[1]);
    user->nickname = mx_strdup(name[2]);
    user->id = mx_strdup(name[3]);
    *((t_table_user**)data) = user;
    return 0;
}

static int get_ok_msg(char **response, t_table_user *tuser) {
    int i = 20;
    int lens[3] = {50, 50, 50};
    int total_len = lens[0] + lens[1] + lens[2] + 23;

    *response = malloc(total_len);
    memset(*response, 0, total_len);
    mx_memcpy(&(*response)[9], tuser->id, strlen(tuser->id));
    mx_memcpy(&(*response)[i], tuser->first_name, lens[0] + 1);
    i += 50 + 1;
    mx_memcpy(&(*response)[i], tuser->second_name, lens[1] + 1);
    i += 50 + 1;
    mx_memcpy(&(*response)[i], tuser->nickname, lens[2] + 1);
    return total_len;
}

int mx_get_msg_user(char *request, t_table_user *tuser, char **response) {
    int total_len =  get_ok_msg(response, tuser);

    mx_memcpy(*response, request, 5);
    *(int*)(&(*response)[5]) = total_len;
    return total_len;
}


char *mx_get_user_info(t_server *server_info, t_server_users *serv_user) {
    char sql[1024];
    t_table_user *user = NULL;
    char *response = NULL;
    char *req = serv_user->buff;

    if (mx_check_number(&req[9], 11) == 0) {
        response = mx_create_response(req[0], *((int *)&req[1]), (char)100);
        fprintf(MX_ERROR_THREAD, "not messege\n");
    }
    sprintf(sql,"select usr_frst_name, usr_scnd_name, usr_nickname, usr_id "
    "from user where usr_id = '%s';", &req[9]);
    mx_do_query(sql,callback, &user, server_info);
    if (user != 0) {
        mx_get_msg_user(req, user, &response);
        mx_free_tuser(user);
        return response;
    }
    response = mx_create_response(req[0], *((int *)&req[1]), (char)107);
    return response;
}
