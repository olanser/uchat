#include "client.h"

gboolean mx_resize_signin_window (GtkWidget *window, t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    printf("HEIGHT = %d and WIDTH = %d\n", height, width);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_main_box), width, height);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_child_box), width, height);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->image_name), width, -1);
    return FALSE;
}

gboolean mx_destroy_signin_window(GtkWidget *window) {
    if (window)
        gtk_window_close(GTK_WINDOW (window));
    exit(0);
    return FALSE;
}

gboolean mx_go_fullscreen_signin_window(GtkWidget *window, GdkEventWindowState *event, t_objects *objs) {
    if (event->changed_mask == GDK_WINDOW_STATE_FULLSCREEN) {
        printf("FULLSCREEN\n");
        sleep(1);
        gtk_window_fullscreen(GTK_WINDOW (window));
        mx_resize_signin_window(window, objs);
    }
    return FALSE;
}
