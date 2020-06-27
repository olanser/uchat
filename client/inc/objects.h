#ifndef OBJECTS_H
#define OBJECTS_H

#include <gtk/gtk.h>

typedef struct s_objects t_objects;
typedef struct s_signin_window t_signin_window;
typedef struct s_signup_window t_signup_window;
typedef struct s_main_chat_window t_main_chat_window;

typedef struct s_info {
    int sock;
    int query_id;
    int scene; // number of window
    t_objects* objs;
}              t_info;

typedef struct s_objects {
    t_signin_window *s_signin_win;
    t_signup_window *s_signup_win;
    t_main_chat_window *chat_win;
} t_objects;


struct s_main_chat_window {
    GtkWidget* chat_win;
    GtkWidget* main_chat_box;
    GtkWidget* profile_set_btn;
    GtkWidget* selected_chat_lbl;
    GtkWidget* paned_chat;
    GtkWidget* search_line;
    GtkWidget* chat_line;
    GtkWidget* send_btn;
    GtkWidget* search_pan_main_box;
    GtkWidget* chat_entry_split_box;
    GtkWidget* search_frame;
    GtkWidget* chat_frame;
};

struct s_signin_window {
    GtkWidget* signin_win;
    GtkWidget* signin_main_box;
    GtkWidget* signin_child_box;
    GtkWidget* signin_login;
    GtkWidget* signin_password;
    GtkWidget* signin_button;
    GtkWidget* signin_vissible_pass;
    GtkWidget* save_user_tick;
};

struct s_signup_window {
    GtkWidget* signup_win;
    GtkWidget* signup_login;
    GtkWidget* signup_pass1;
    GtkWidget* signup_pass2;
    GtkWidget* signup_buton;
    GtkWidget* signup_vissible_pass;
    GtkWidget* signup_main_grid;
    GtkWidget* signup_child_box;
};

#endif