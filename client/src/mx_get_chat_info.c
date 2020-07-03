#include "client.h"
#include "libmx.h"

/* find listbox of chat */
t_chat_info* mx_get_chat_info(t_list* list, int id_chat) {
    t_list* tmp = list;
    while (tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == id_chat)
            return ((t_chat_info*)tmp->data);
        tmp = tmp->next;
    }
    return 0;
}
