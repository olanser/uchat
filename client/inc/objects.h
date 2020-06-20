#ifndef OBJECTS_H
#define OBJECTS_H

#include <gtk/gtk.h>

typedef struct s_objects t_objects;
typedef struct s_main_window t_main_window;

typedef struct s_info {
    int sock;
    int query_id;
    int scene; // number of window
    t_objects* objs;
}              t_info;

typedef struct s_objects {
    t_main_window *s_main_win;
} t_objects;

typedef struct s_main_window {
    GtkWidget* wid_main_win;
} t_main_window;

#endif
