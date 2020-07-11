#include "client.h"

gboolean mx_resize_main_window (GtkWidget *window, t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    if (objs->chat_win->size->width != width || objs->chat_win->size->height != height) {
        objs->chat_win->size->width = width;
        objs->chat_win->size->height = height;
        gtk_paned_set_position(GTK_PANED (objs->chat_win->paned_chat), objs->chat_win->size->position);
    }
    else {
        gtk_widget_set_size_request(GTK_WIDGET (objs->chat_win->main_chat_box), width, height);
        objs->chat_win->size->position = gtk_paned_get_position(GTK_PANED (objs->chat_win->paned_chat));
    }
    return FALSE;
}

gboolean mx_destroy_main_window(GtkWidget *window) {
    if (window)
        gtk_window_close(GTK_WINDOW (window));
    exit(0);
    return FALSE;
}
