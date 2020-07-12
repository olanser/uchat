#include "client.h"

void mx_expand_changed(GtkWidget *widget, void* data) {
    t_info* info = (t_info*)data;
    char *str = (char*)gtk_entry_get_text(GTK_ENTRY(widget));

    mx_api_show_users(str, info);
}
