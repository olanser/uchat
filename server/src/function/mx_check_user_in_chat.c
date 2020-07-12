#include "server.h"

bool mx_check_user_in_chat(int id_chat, int id_user,
                           t_server *server_info) {
    char sql[85];
    int check = 0;

    sprintf(sql, "SELECT * FROM cou where cou_chat_id = '%d' AND cou_usr_id "
            "= '%d';", id_chat, id_user);
    if (mx_do_query(sql, mx_callback_count, &check, server_info) == 0) {
        if (check != 0) {
            return 1;
        }
    }
    return 0;
}
