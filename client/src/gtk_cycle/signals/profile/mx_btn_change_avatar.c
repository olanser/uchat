#include "client.h"
#include "defines_client.h"

void mx_btn_change_avatar(GtkWidget *button, GdkEvent *event,  t_info *info) {
    int *ava = g_object_get_data(G_OBJECT(button), "avatar");

    gtk_image_set_from_file(
        GTK_IMAGE(info->objs->s_win_profile->profile_img), 
        mx_get_path_to_ava(*ava));
    info->user_info->avatar = *ava;
    mx_api_change_avatar(info->user_info->avatar, info);
}
