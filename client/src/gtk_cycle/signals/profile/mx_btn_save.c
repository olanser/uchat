#include "client.h"
#include "defines_client.h"

void mx_btn_save(GtkWidget* button, t_info *info) {
    gtk_widget_hide(info->objs->s_win_profile->box_profile);
    gtk_widget_set_sensitive(info->objs->chat_win->main_chat_box, TRUE);
}
