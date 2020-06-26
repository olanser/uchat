/*
* Connect all signals to gtk window
*/
#include "client.h"

// void mx_resize_emitted(GtkWidget *window, t_objects *objs) {
//     GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
//     GtkRequisition *new_size = gtk_requisition_new();
//     GtkRequisition *size = gtk_requisition_new();
//     int height = gdk_window_get_height(gdk_window);
//     int width = gdk_window_get_width(gdk_window);

//     size->height = 750;
//     size->width = 1350;
//     if (height != 750 && width != 1350) {
//         printf("height = %d and width = %d\n", height, width);
//         new_size->height = height;
//         new_size->width = width;
//         // gtk_widget_get_preferred_size(GTK_WIDGET (objs->s_signin_win->signin_main_box), size, new_size);
//         // gtk_widget_get_preferred_size(GTK_WIDGET (objs->s_signin_win->signin_child_box), size, new_size);
//         gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_main_box), width, height);
//         gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_child_box), width, height);
//     }
//     gtk_requisition_free(new_size);
//     gtk_requisition_free(size);
// }

void mx_connect_signals(t_info* info) {
    // g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "size-allocate", (GCallback) mx_resize_emitted, info->objs);
    // all signals here
}
