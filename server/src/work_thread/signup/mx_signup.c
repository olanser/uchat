#include "server.h"
#include "defines.h"

int check_lens(t_table_user *tuser) {
    if (mx_strlen(tuser->first_name) > 50) {
        fprintf(MX_ERROR_THREAD, "Error: first name too long\n");
        return 1;
    }   
    if (mx_strlen(tuser->second_name) > 50) {
        fprintf(MX_ERROR_THREAD, "Error: second name too long\n");
        return 2;
    }
    if (mx_strlen(tuser->nickname) > 100) {
        fprintf(MX_ERROR_THREAD, "Error: nickname too long\n");
        return 3;
    }
    if (mx_strlen(tuser->second_name) > 100) {
        fprintf(MX_ERROR_THREAD, "Error: password too long\n");
        return 4;
    }
    return 0;
}

bool is_nickname_free(char *nickname, t_server *server_info) {
    char sql[300];
    int count = 0;

    sprintf(sql, "select usr_nickname from user where user.usr_nickname = "
            "'%s';", nickname);
    if (mx_do_query(sql, mx_callback_count, &count, server_info) != SQLITE_OK)
        return 1;
    if (count != 0) {
       return false;
    }
    return true;
}

int check_tuser(t_table_user *tuser, t_server *server_info) {
    if (check_lens(tuser) != 0)
        return MX_QS_ERR_SERV;
    if (mx_check_symbols(tuser)) {
        return MX_QS_ERR_SERV;
    }
    if (!is_nickname_free(tuser->nickname, server_info)) {
        return MX_QS_ERR_REG;
    }
    return MX_QS_OK;
}

int change_db( t_server *server_info, t_table_user *tuser) {
    char sql[500];

    sprintf(sql, "insert into user values(NULL, '%s', '%s', '%s', '%s', 1, '%c');",
        tuser->first_name, tuser->second_name, tuser->nickname, tuser->pass, 1);
    if (mx_do_query(sql, 0, 0, server_info) != SQLITE_OK) {
        printf("ERROR SQL\n");
        return 1;
    }
        
    return 0;
}

static char get_status(t_table_user *tuser, t_server *server_info) {
    char status = (char)MX_QS_OK;

    status = (char)check_tuser(tuser, server_info);
    if (status == MX_QS_ERR_REG) { // nickname busy
    }
    else if (status == MX_QS_ERR_SERV || change_db(server_info, tuser) != 0) {
        status = MX_QS_ERR_SERV;
    }
    return (char)status;
}

static int set_tuser(char *request, t_table_user *tuser) {
    tuser->first_name = &request[9];
    tuser->second_name = &request[60];
    tuser->nickname = &request[111];
    tuser->pass = &request[212];
    return 0;
}

int get_response(char *request, char **response, char status,
                t_server_users *user) {
    if (status != (char)200) {
        *response = malloc(sizeof(char) * 10);
        mx_memcpy(*response,  request, 5);
        memset(&(*response)[5], 0, 4);
        (*response)[5] = 10; // size
        (*response)[9] = status; // status
        return 10;
    }
    *response = malloc(sizeof(char) * 21);
    mx_memcpy(*response,  request, 5);
    memset(&(*response)[5], 0, 4);
    (*response)[5] = 14; // size
    (*response)[9] = status; // status
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
    free(tuser);
    return respons;
}
