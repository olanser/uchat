#include "header.h"


static t_user_in_chat *create_chat_users(char *user_id, char *usr_nick) {
    t_user_in_chat *node = (t_user_in_chat *)malloc(sizeof(t_user_in_chat));

    node->usr_id = strdup(user_id);
    node->usr_nickname = strdup(usr_nick);
    node->next = NULL;
    return node;
}

void mx_push_char_users(t_user_in_chat **list, char *user_id, char *usr_nick) {
    t_user_in_chat *node = create_chat_users(user_id, usr_nick);
    t_user_in_chat *buf = *list;

    if (*list == NULL)
        *list = node;
    else {
        while (buf->next != NULL)
            buf = buf->next;
        buf->next = node;
    }

}
void mx_delete_chat_users(t_user_in_chat **list) {
    t_user_in_chat *tmp = NULL;

    while ((*list)) {
        tmp = (*list)->next;
        free((*list)->usr_id);
        free((*list)->usr_nickname);
        free((*list));
        *list = tmp;
    }
}
