#include "client.h"

void mx_btn_send_msg_clicked(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    char *argv[2] = {info->id_chat, (char*)get_text_of_textview(info->objs->chat_win->chat_line)};

    mx_api_send_message(argv, info);
    free(argv[1]);
}
