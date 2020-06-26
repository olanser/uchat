#include "header.h"

static bool check_time(char *time) {
    for (int i = 0; i < 20; i++) {
        if (i == 4 || i == 7) { 
            if (time[i] != '-')
                return 1;
        }
        else if (i == 10) {
            if (time[i] != ' ')
            return 1;
        }
        else if (i == 13 || i == 16) {
            if (time[i] != ':')
                return 1;
        }
        else if (i == 19) {
            if (time[i] == 0)
            return 0;
        }
        else if (time[i] < '0' || time[i] > '9') {
            return 1;
        }
    }
    return 1;
}


int mx_get_msgs_time(void *request, char **response, t_user *user_info) {
    char sql[1024];
    t_list *head = 0;

    mx_create_response(request, response);
    if (check_time(&((char*)request)[9])) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        (*response)[9] = (char)100;
        return 10;
    }
    sprintf(sql, "select msg.msg_id, msg.msg_chat_id, msg.msg_creator, msg.msg_send_time, msg.msg_data, msg.msg_status, msg.msg_status_see from msg where msg.msg_chat_id in (select cou.cou_char_id  from cou where cou.cou_usr_id == %s) and msg.msg_send_time >= '%s';", user_info->id, &((char*)request)[9]);
    mx_do_query(sql, mx_callback_updates,user_info);
    (*response)[9] = (char)200;
    return 10;
}
