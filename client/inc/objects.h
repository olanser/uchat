#ifndef OBJECTS_H
#define OBJECTS_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "characters.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

typedef struct s_objects t_objects;
typedef struct s_signin_window t_signin_window;
typedef struct s_signup_window t_signup_window;
typedef struct s_main_chat_window t_main_chat_window;
typedef struct s_user_info t_user_info;
typedef struct s_msg_widget t_msg_widget;
typedef struct s_msg t_msg;
typedef struct s_win_profile t_win_profile;
typedef struct s_win_size t_win_size;

typedef struct s_info {
    int sock;
    SSL *ssl;
    SSL_CTX *ctx;
    int query_id;
    int scene; // number of window
    int id_chat;
    int id_of_editing_msg; /* if we now edit msg else 0*/
    int id_of_editing_chat; /* if we now edit msg else 0*/
    t_list* list_of_files; // t_file list of sending files
    t_list* list_of_chats; // t_chat_info
    t_list* list_of_recv_files; // list of receiving files
    t_user_info* user_info; // our user
    t_objects* objs;
    pthread_mutex_t m_file_list;
    pthread_mutex_t m_file_recv_list;
    pthread_mutex_t m_write_sock;
    t_characters *chars;
}              t_info;

typedef struct s_user_info {
    char id;
    char avatar;
    char* nickname;
    char* frst_name;
    char* scnd_name;
} t_user_info;

typedef struct s_file {
    int fd;
    int chat_id; // chat where sended
    t_msg* msg_of_file;
    size_t size; // size of file
    size_t pos; // current pos in file
    char *name; // reak naem
    long long unique_name; // unique name for file
} t_file;

typedef struct s_chat_info {
    int node_index;
    int chat_id;
    int last_id_msg;
    int type_of_chat; // 50 - chat, 49 - dialog
        int id_user; // for dialogs
    char *name;
    t_list *msgs; // t_msg list of msgs
    GtkWidget* list_box; // list box of msgs
    GtkWidget* chat_widget; // button widget(in left box)
}t_chat_info;

/*
* structure for describe msg
*
* msg type:
*   1 - msg;
*   2 - sticker;
*   3 - file;
*
* msg_f_type:
*   1 - img;
*   2 - text;
*   3 - video;
*   4 - audio;
*   5 - zip;
*/
typedef struct s_msg{
    int msg_id;
    int msg_id_chat;
    int msg_id_user;
    char* msg_time;
    char msg_avatar;
    char* msg_data;
    int msg_type;
    char *msg_f_name_of_file;
    char msg_f_type;
    int msg_f_size; // size_of_file
    t_msg_widget *msg_widget;    
} t_msg;

typedef struct s_tag {
    int start;
    int end;
    char *pango; // pango format
    char *uchat; // uchat format
} t_tag;

typedef struct s_msg_widget {
    GtkWidget *widget;
    GtkWidget *label;
} s_msg_widget;

typedef struct s_objects {
    t_signin_window *s_signin_win;
    t_signup_window *s_signup_win;
    t_win_profile *s_win_profile;
    t_main_chat_window *chat_win;
} t_objects;


struct s_main_chat_window {
    t_win_size *size;
    GtkWidget* layout_main;
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
    GtkWidget* expand_users;
    GtkWidget* search_users;
    GtkWidget* btn_choose_file;
    GtkWidget* btn_logout;
    GtkWidget* list_box_users;
    GtkWidget* send_img;
    GtkWidget* exit_img;
    GtkWidget* settings_img;
    GtkWidget* stickers_img;
    GtkWidget* attach_img;
    GtkWidget* new_chat_img;
        GtkWidget **user_widgets; // mass

    // stickers
    GtkWidget* btn_show_sticker; // change
    GtkWidget* notebook_stickers;

    // settings
    GtkWidget* btn_settings;
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
    GtkWidget *layout;
    GtkWidget *image_name;
    GtkWidget *broken_screen;
    GtkWidget *broken_lbl;
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
    GtkWidget* btn_go_to_signin;
};

typedef struct s_win_profile {
    GtkWidget* box_profile;
    GtkWidget* theme1_btn;
    GtkWidget* theme2_btn;
    GtkWidget* theme3_btn;
    GtkWidget* theme4_btn;
    GtkWidget* theme5_btn;
    GtkWidget* save_btn;
    GtkWidget* profile_img;
    GtkWidget* ev_box_profile_img;
    GtkWidget* grid_avatars;
    GtkWidget* login_lbl;
} t_win_profile;

struct s_win_size {
    int height;
    int width;
    int position;
};

#endif
