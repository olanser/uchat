#ifndef OBJECTS_H
#define OBJECTS_H

#include <gtk/gtk.h>
#include "libmx.h"

typedef struct s_objects t_objects;
typedef struct s_signin_window t_signin_window;
typedef struct s_signup_window t_signup_window;
typedef struct s_main_chat_window t_main_chat_window;
typedef struct s_user_info t_user_info;

typedef struct s_info {
    int sock;
    int query_id;
    int scene; // number of window
    int id_chat;
    t_list* list_of_chats; // for checko=ing chats when add
    t_user_info* user_info;
    t_objects* objs;
}              t_info;

typedef struct s_user_info {
    char avatar;
    char* nickname;
    char* frst_name;
    char* scnd_name;
} t_user_info;

typedef struct s_chat_info {
    int node_index;
    int chat_id;
    t_list *msgs; // t_msg list of msgs
    GtkWidget* list_box; // list box of msgs
}t_chat_info;

typedef struct s_msg{

} t_msg;

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
    GtkWidget* notebook;
    GtkWidget* search_frame;
    GtkWidget* chat_frame;
    GtkWidget* listbox_search;
    GtkWidget* search_viewport1;
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
