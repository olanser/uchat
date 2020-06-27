#include "client.h"

gboolean mx_resize_main_window (GtkWidget *window, t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);
    int position = gtk_paned_get_position(GTK_PANED (objs->chat_win->paned_chat));

    gtk_widget_set_size_request(GTK_WIDGET (objs->chat_win->main_chat_box), width, height);
    return FALSE;
}

gboolean mx_destroy_main_window(GtkWidget *window) {
    if (window)
        gtk_window_close(GTK_WINDOW (window));
    return FALSE;
}
