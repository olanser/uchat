#include "client.h"
#include "defines_client.h"

void mx_btn_change_avatar(GtkWidget *button, GdkEvent *event,  t_info *info) {
    int *ava = g_object_get_data(G_OBJECT(button), "avatar");

    info->user_info->avatar = *ava;
    mx_api_change_avatar(info->user_info->avatar, info);
}