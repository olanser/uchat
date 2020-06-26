#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

bool mx_check_user_in_char(char *id_chat, char *id_user) {
    char sql[85];

    int check = 0;
    sprintf(sql, "SELECT * FROM cou where cou_char_id = %s AND cou_usr_id = %s;", id_chat, id_user);
    if (mx_do_query(sql, callback, &check) == 0) {
        if (check != 0) {
            return 1;
        }
    }
    return 0;
}