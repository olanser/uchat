#include "client.h"

gboolean mx_expand_focus_in(GtkWidget *widget, GdkEvent  *event,
                            void* data) {
    t_info* info = (t_info*)data;

    gtk_widget_show(info->objs->chat_win->list_box_users);
    return FALSE;
}
