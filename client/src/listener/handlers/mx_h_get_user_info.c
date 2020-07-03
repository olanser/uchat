#include "client.h"
#include "libmx.h"

t_chat_info *get_dialog_info(int id_user, t_list *list_of_chats) {
    t_list *tmp = list_of_chats;

    while(tmp) {
        if (((t_chat_info*)tmp->data)->id_user == id_user) {
            if (((t_chat_info*)tmp->data)->name == 0)
                return ((t_chat_info*)tmp->data);
            else 
                return 0; // now have label
        }
        tmp = tmp->next;
    }
    return 0; // didnt find with that id
}

void update_dialogs(char *response, t_info *info) {
    t_chat_info *chat_info = get_dialog_info(*(int*)&response[9], info->list_of_chats);

    if (chat_info == 0)
        return;
        
    chat_info->name = mx_strdup(&response[13]);
    gtk_button_set_label(GTK_BUTTON(chat_info->chat_widget), &response[13]);
}

int mx_h_get_user_info(char *response, t_info *info) {
    update_dialogs(response, info);
    
    return 0;
}
