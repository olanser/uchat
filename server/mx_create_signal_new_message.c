#include "header.h"
static int callback(void *data, int columns, char **name, char **tabledata) {
    mx_push_front(((t_list **)(data)), mx_strdup(name[0]));
    return 0;
}

void mx_create_signal_new_message(char *id_chat) {
    char *sql = malloc(1024);
    t_list *head = 0;
    sprintf(sql, "select distinct pd.pd_pid from pd where pd.pd_user_id in (select cou_usr_id  from cou where cou.cou_char_id == %s);", id_chat);

    mx_do_query(sql, callback, &head);
    while (head) {
        kill(atoi(head->data), SIGUSR1);
        mx_pop_front(&head);
    }
    free(sql);
}
