#include "client.h"

void mx_btn_send_msg_clicked(GtkWidget* button, void* data) {
    t_info *info = (t_info*) data;
    char *argv[2] = {"1", "PRIVETT!"};

    mx_api_send_message(argv, info);
}
