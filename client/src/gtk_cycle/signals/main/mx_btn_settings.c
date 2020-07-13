#include "client.h"

void mx_btn_settings(GtkWidget *btn, t_info *info) {
    gtk_widget_show_all(info->objs->s_win_profile->box_profile);
    gtk_widget_set_sensitive(info->objs->chat_win->main_chat_box, FALSE);
}
