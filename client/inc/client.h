#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include "objects.h"

void mx_init(t_info **info);
void mx_init_gtk(t_info* info);
int mx_chang_scene(t_info *info, int scene);
void mx_do_iteration(t_info* info);
void mx_show_window(t_info* info);
void mx_connect_signals(t_info* info);


//signals_callback_func
gboolean mx_resize_signup_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_signin_window (GtkWidget *window, t_objects *objs);
gboolean mx_resize_main_window (GtkWidget *window, t_objects *objs);
gboolean mx_destroy_main_window(GtkWidget *window);
gboolean mx_destroy_signup_window(GtkWidget *window);
gboolean mx_destroy_signin_window(GtkWidget *window);
//

#endif
