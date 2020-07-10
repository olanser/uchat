#include "client.h"

void mx_btn_send_sticker(GtkWidget *button, GdkEvent*event, void *data) {
    t_info* info = (t_info*)data;
    char* path = g_object_get_data(G_OBJECT(button), "path_to_sticker");

    printf("path = %s\n", path);
    mx_api_send_message(info->id_chat, path, 2, info);
}
