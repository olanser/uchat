#include "client.h"

void mx_btn_del_msg(GtkWidget *button, GdkEvent*event, void *data) {
    t_info* info = (t_info*)data;
    int *id_msg = g_object_get_data(G_OBJECT(button), "id_msg");
    printf("del id_msg = %d\n", *id_msg);
    mx_api_delete_message(*id_msg, info->id_chat, info);
}
