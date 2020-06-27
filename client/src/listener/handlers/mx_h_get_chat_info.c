#include "client.h"

static bool is_exist(char *id, t_list* list_of_chats) {
    t_list* tmp = list_of_chats;

    while(tmp) {
        if (mx_strcmp(((t_chat_info*)tmp->data)->chat_id, id) == 0) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

/* 
* add button to the left list box,
* create widget for new list of msgs
* add new node to list of chats
*/
static void add_new_chat(char *response, t_info *info) {
    GtkWidget* list_box_dialogs = info->objs->chat_win->listbox_dialogs;
    GtkWidget* chat_label = gtk_label_new(&response[21]);
    t_chat_info* chat_info = malloc(sizeof(t_chat_info));

    chat_info->chat_id = mx_strdup(&response[21]);
    mx_push_back(&info->list_of_chats, chat_info);
    g_object_set_data(G_OBJECT(chat_label), "chat_info", chat_info);
}

int mx_h_get_chat_info(char *response, t_info *info) {
    
    
    if(is_exist(&response[21], info->list_of_chats))
        return 1;
    add_new_chat(response, info);

    printf("id = %s\n", &response[21]);
    // GtkWidget* chat_label = gtk_label_new(&response[21]);
    // t_chat_info* chat_info = malloc(sizeof(t_chat_info));

    // chat_info->chat_id = mx_strdup(&response[21]);
    // mx_push_back(&info->list_of_chats, chat_info);
    // g_object_set_data(G_OBJECT(chat_label), "chat_info", chat_info);
    return 0;
}
