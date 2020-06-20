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

#endif
