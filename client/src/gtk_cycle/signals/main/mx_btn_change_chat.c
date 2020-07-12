#include "client.h"

void mx_btn_change_chat(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    t_chat_info* ch = 0;
    t_chat_info* chat_info = g_object_get_data(G_OBJECT(button), "chat_info");

    ch = g_object_get_data(G_OBJECT(button), "chat_info");
    info->id_chat = ch->chat_id;
    gtk_notebook_set_current_page(GTK_NOTEBOOK(
        info->objs->chat_win->notebook), ch->node_index);
    mx_api_get_chat_msgs(chat_info->chat_id, chat_info->last_id_msg, 10,
                         info);
}
