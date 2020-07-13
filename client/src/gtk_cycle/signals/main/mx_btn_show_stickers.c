#include "client.h"

void mx_btn_show_stickers(GtkWidget* button, t_info* info) {
    bool vis = gtk_widget_get_visible(
        info->objs->chat_win->notebook_stickers);

    gtk_widget_set_visible(info->objs->chat_win->notebook_stickers, !vis);
}
