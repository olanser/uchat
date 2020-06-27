#include "client.h"

gboolean mx_resize_signin_window (GtkWidget *window, t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_main_box), width, height);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_child_box), width, height);
    return FALSE;
}

gboolean mx_destroy_signin_window(GtkWidget *window) {
    if (window)
        gtk_window_close(GTK_WINDOW (window));
    return FALSE;
}
