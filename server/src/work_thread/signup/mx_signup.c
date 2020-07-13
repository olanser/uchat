#include "server.h"
#include "defines.h"

int change_db( t_server *server_info, t_table_user *tuser) {
    char sql[500];

    sprintf(sql, "insert into user values(NULL, '%s', '%s', '%s', '%s', 1, "
        "'%c');", tuser->first_name, tuser->second_name, tuser->nickname,
        tuser->pass, 1);
    if (mx_do_query(sql, 0, 0, server_info) != SQLITE_OK) {
        printf("ERROR SQL\n");
        return 1;
    }
    return 0;
}

static char get_status(t_table_user *tuser, t_server *server_info) {
    char status = (char)MX_QS_OK;

    status = (char)mx_check_tuser(tuser, server_info);
    if (status == MX_QS_ERR_REG) { // nickname busy
    }
    else if (status == MX_QS_ERR_SERV || change_db(server_info, tuser) != 0) {
        status = MX_QS_ERR_SERV;
    }
    return (char)status;
}

static int set_tuser(char *request, t_table_user *tuser) {
    int j = 0;
    char temp[256];

    for (int i = 212; i < 276; i++, j += 2)
        sprintf(&temp[j], "%02x", (unsigned char)request[i]);
    temp[124] = 0;
    tuser->pass = mx_strdup(temp);
    tuser->first_name = &request[9];
    tuser->second_name = &request[60];
    tuser->nickname = &request[111];
    return 0;
}

int get_response(char *request, char **response, char status,
                t_server_users *user) {
    if (status != (char)200) {
        *response = malloc(sizeof(char) * 10);
        mx_memcpy(*response,  request, 5);
        memset(&(*response)[5], 0, 4);
        (*response)[5] = 10; 
        (*response)[9] = status;
        return 10;
    }
    *response = malloc(sizeof(char) * 21);
    mx_memcpy(*response,  request, 5);
    memset(&(*response)[5], 0, 4);
    (*response)[5] = 14;
    (*response)[9] = status;
    *(int*)(&(*response)[10]) = user->id_users;
    return 14;
}

char *mx_signup(t_server *server_info, t_server_users *user) {
    t_table_user *tuser = malloc(sizeof(t_table_user));
    char status = 0;
    char *respons = 0;

    if (set_tuser(user->buff, tuser) != 0) {
        status = MX_QS_ERR_SERV;
    }
    else {
        status = get_status(tuser, server_info);
    }
    if (status == (char)MX_QS_OK)
        mx_update_user(tuser, user, server_info);
    get_response(user->buff, &respons, status, user);
    free(tuser->pass);
    free(tuser);
    return respons;
}
