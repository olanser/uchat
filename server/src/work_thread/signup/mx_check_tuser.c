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

int mx_check_tuser(t_table_user *tuser, t_server *server_info) {
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
