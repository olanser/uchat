#include "client.h"

void mx_btn_settings(GtkWidget *btn, t_info *info) {
    gtk_widget_show_all(info->objs->s_win_profile->box_profile);
    gtk_image_set_from_file(
        GTK_IMAGE(info->objs->s_win_profile->profile_img),
        mx_get_path_to_ava(info->user_info->avatar));
    printf("info->user_info->avatar = %d\n", info->user_info->avatar);
    gtk_widget_set_sensitive(info->objs->chat_win->main_chat_box, FALSE);
}
