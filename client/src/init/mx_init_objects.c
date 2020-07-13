#include "client.h"
#include "defines_client.h"

void mx_init_objects(GtkBuilder *builder, t_objects *objs, t_info*info) {
    mx_init_signin_win(builder, objs->s_signin_win);
    mx_init_signup_win(builder, objs->s_signup_win);
    mx_init_main_chat_win(builder, objs->chat_win, info);
}

void mx_set_signin_win_properties(t_signin_window *signin) {
    gtk_widget_set_size_request(signin->signin_win, 1350, 750);
    gtk_widget_show_all(signin->signin_win);
}

void mx_set_signup_win_properties(t_signup_window *signup) {
    gtk_widget_set_size_request(signup->signup_win, 540, 300);
    gtk_widget_show_all(signup->signup_win);
}

void mx_set_main_chat_properties(t_main_chat_window *main_chat) {
    gtk_widget_set_size_request(main_chat->chat_win,
                                MX_WIN_WIDTH, MX_WIN_HEIGHT);
    gtk_widget_set_size_request(GTK_WIDGET (main_chat->main_chat_box), 
                                MX_WIN_WIDTH, MX_WIN_HEIGHT);
    gtk_paned_set_position(GTK_PANED (main_chat->paned_chat), 171);
    gtk_widget_hide(main_chat->chat_win);
}

void mx_set_properties(t_objects *objs) {
    mx_set_signin_win_properties(objs->s_signin_win);
    mx_set_signup_win_properties(objs->s_signup_win);
    mx_set_main_chat_properties(objs->chat_win);
}
