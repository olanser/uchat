#include "client.h"

gboolean mx_expand_focus_out (GtkWidget *widget, GdkEvent  *event, void* data) {
    t_info* info = (t_info*)data;

    gtk_widget_hide(info->objs->chat_win->list_box_users);
    return FALSE;
}
