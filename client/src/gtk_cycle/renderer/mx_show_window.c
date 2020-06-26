/* 
* Author vbalachevs
* cycle for show window
*/
#include "client.h"
#include "defines.h"

// static void resize(t_objects *objs) {
//     GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->s_signin_win->signin_win));
//     int height = gdk_window_get_height(gdk_window);
//     int width = gdk_window_get_width(gdk_window);

//     printf("height = %d and width = %d\n", height, width);
// }

void mx_show_window(t_info* info) {
    while(1) {
        // resize(info->objs);
        mx_do_iteration(info);
    }
}
