#include "header.h"

void* updates(void *data) {
    int signo;
    t_user *user_info = data;
    char sql[1024];

    while (1) {
        sigwait(&(user_info->updates->newmask), &signo);
        if (signo == SIGUSR1) {
            printf("GET SIGNAL\n");
            sprintf(sql, "select msg.msg_id, msg.msg_chat_id, msg.msg_creator, msg.msg_send_time, msg.msg_data, msg.msg_status, msg.msg_status_see, msg.msg_file_type, msg.msg_file_name, msg.msg_file_size from msg where msg.msg_chat_id in (select cou.cou_char_id  from cou where cou.cou_usr_id == %s) and msg.msg_send_time >= '%s';", user_info->id, user_info->updates->time);
            mx_do_query(sql, mx_callback_updates, data);
        }
    }
    return (void*)0;
}

pthread_t mx_create_pthread_updates(t_user *user_info) {
    pthread_t preg;

    pthread_create(&preg, 0, updates, user_info);
    return preg;
}
