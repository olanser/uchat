#include "client.h"

bool mx_is_chat_exist(char id, t_list* list_of_chats) {
    t_list* tmp = list_of_chats;

    while(tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == id) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}
