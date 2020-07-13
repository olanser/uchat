#include "client.h"

gboolean mx_resize_signup_window (GtkWidget *window, t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    gtk_widget_set_size_request(
        GTK_WIDGET(objs->s_signup_win->signup_main_grid), width, height);
    gtk_widget_set_size_request(
        GTK_WIDGET(objs->s_signup_win->signup_child_box), width, height);
    gtk_widget_set_size_request(
        GTK_WIDGET(objs->s_signup_win->image_name), width, -1);
    return FALSE;
}

gboolean mx_destroy_signup_window(GtkWidget *window) {
    if (window)
        gtk_window_close(GTK_WINDOW (window));
    exit(0);
    return FALSE;
}
