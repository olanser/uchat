#include "client.h"

void mx_btn_send_msg_clicked(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    char*str = 0;

    str = (char*)get_text_of_textview(info->objs->chat_win->chat_line);
    if (mx_strlen(str) > 1000) {
        free(str);
        return;
    }
    if (info->user_info == 0)
        return;
    if (info->id_of_editing_msg == 0)
        mx_api_send_message(info->id_chat, str, 1, info);
    else {
        mx_api_edit_message(info->id_of_editing_chat, 
                            info->id_of_editing_msg, str, info);
        info->id_of_editing_chat = 0;
        info->id_of_editing_msg = 0;
        gtk_widget_set_name(info->objs->chat_win->chat_line, "chat_line");
    }
    free(str);
}
