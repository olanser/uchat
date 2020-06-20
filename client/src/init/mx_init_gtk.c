/* 
* Author vbalachevs
* load all objects an signals from builder
*/
#include "client.h"
#include "defines.h"

void mx_init_main_win(GtkBuilder *builder, t_main_window *main) {
    main->wid_main_win = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    if (main->wid_main_win == 0) {
        fprintf(stderr, "error of open file!\n");
    }
}

void mx_init_objects(GtkBuilder *builder, t_objects *objs) {
    mx_init_main_win(builder, objs->s_main_win);
}

void mx_set_properties(t_objects *objs) {
    gtk_widget_set_size_request(objs->s_main_win->wid_main_win, 400, 400);
}

void mx_connect_builder(t_info* info) {
    GtkBuilder* builder = gtk_builder_new_from_file(MX_PATH_TO_TEMPLATE);
    mx_init_objects(builder, info->objs);
    mx_set_properties(info->objs);
}

void mx_init_gtk(t_info* info) {
    mx_connect_builder(info); 
    mx_connect_signals(info);
}
