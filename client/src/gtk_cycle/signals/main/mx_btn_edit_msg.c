#include "client.h"

void mx_btn_edit_msg(GtkButton *button, GdkEvent *event, void *data) {
    t_info* info = (t_info*)data;
    int *id_msg = g_object_get_data(G_OBJECT(button), "id_msg");
    GtkTextView *textview = GTK_TEXT_VIEW(info->objs->chat_win->chat_line);
    GtkTextBuffer* buff = gtk_text_view_get_buffer(textview);
    t_msg *msg = mx_find_msg(info->list_of_chats, *id_msg, info->id_chat);

    info->id_of_editing_msg = *id_msg;
    info->id_of_editing_chat = info->id_chat;
    gtk_widget_set_name(info->objs->chat_win->chat_line, "chat_line_editing");
    gtk_text_buffer_set_text(buff, msg->msg_data, -1);
}
