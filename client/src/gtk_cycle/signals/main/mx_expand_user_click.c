#include "client.h"

gboolean mx_expand_user_click(GtkWidget* widget, GdkEvent* event,
                              void* data) {
    t_info *info = (t_info*)data;
    t_user_info* user_info = g_object_get_data(G_OBJECT(widget), "user_info");

    mx_go_to_dialog(info, user_info->id);
    return FALSE;
}