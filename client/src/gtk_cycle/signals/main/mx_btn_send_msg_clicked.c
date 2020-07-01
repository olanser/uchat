#include "client.h"

void mx_btn_send_msg_clicked(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    char*str = 0;

    str = (char*)get_text_of_textview(info->objs->chat_win->chat_line);
    if (info->user_info == 0)
        return;
    mx_api_send_message(info->id_chat, str, info);
    free(str);
}
