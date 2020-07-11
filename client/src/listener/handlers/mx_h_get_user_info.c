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

gboolean update_dialogs(void *data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];
    t_chat_info *chat_info = get_dialog_info(*(int*)&response[9], info->list_of_chats);

    if (chat_info == 0)
        return false;
    chat_info->name = mx_strdup(&response[115]);
    gtk_button_set_label(GTK_BUTTON(chat_info->chat_widget), &response[115]);
    free(response);
    free(data);
    return false;
}

int mx_h_get_user_info(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);
    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, update_dialogs, data, 0);
    return 0;
}
