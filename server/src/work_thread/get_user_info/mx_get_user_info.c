#include "server.h"
#include "defines.h"

static void mx_free_tuser(t_table_user *tuser) {
    free(tuser->first_name);
    free(tuser->second_name);
    free(tuser->nickname);
    free(tuser);
}

static int callback(void *data, int column, char **name, char **tabledata) {
    t_table_user *user =  malloc(sizeof(t_table_user));
   
    user->first_name = mx_strdup(name[0]);
    user->second_name = mx_strdup(name[1]);
    user->nickname = mx_strdup(name[2]);
    user->id = atoi(name[3]);
    *((t_table_user**)data) = user;
    return 0;
}

static int get_ok_msg(char **response, t_table_user *tuser) {
    int total_len = 216;

    *response = malloc(total_len);
    memset(*response, 0, total_len);
    *((int*)&(*response)[9]) = tuser->id;
    mx_memcpy(&(*response)[13], tuser->first_name, strlen(tuser->first_name));
    mx_memcpy(&(*response)[64], tuser->second_name, strlen(tuser->second_name));
    mx_memcpy(&(*response)[115], tuser->nickname, strlen(tuser->nickname));
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

    sprintf(sql,"select usr_frst_name, usr_scnd_name, usr_nickname, usr_id "
    "from user where usr_id = '%d';", *((int*)&req[9]));
    if (mx_do_query(sql,callback, &user, server_info) != SQLITE_OK)
        return mx_create_respons_error_and_log(server_info, serv_user, MX_SQL_ERROR,
                                               MQ_QS_ERR_SQL);
    if (user != 0) {
        mx_get_msg_user(req, user, &response);
        mx_free_tuser(user);
        return response;
    }
    return mx_create_respons_error_and_log(server_info, serv_user,
                "USER NOT FOUND!! ", MQ_QS_NOT_FOUND);
}
