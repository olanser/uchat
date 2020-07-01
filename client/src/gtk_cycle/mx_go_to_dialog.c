#include "client.h"

static int get_node_index(t_list* chats, int chat_id) {
    t_list *tmp = chats;
    while (tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == chat_id)
            return ((t_chat_info*)tmp->data)->node_index;
        tmp = tmp->next;
    }
    return -1; // not finded
}

void mx_go_to_dialog(t_info*info, int user_id) {
    // if (get_node_index(info->list_of_chats, chat_id) != -1) {
    //     mx_change_chat(info, chat_id);
    // }
    // else { // new dialog
        
    // }
    // new dialog
    mx_api_create_dialog(user_id, info);
}