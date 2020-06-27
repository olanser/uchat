/* 
* Author vbalachevs
* load all objects an signals from builder
*/
#include "client.h"
#include "defines.h"

void mx_init_signup_win(GtkBuilder *builder, t_signup_window *signup) {
    signup->signup_win = GTK_WIDGET(gtk_builder_get_object(builder, "signup_window"));
    if (signup->signup_win == 0)
        fprintf(stderr, "error of open file!\n");
    signup->signup_buton = GTK_WIDGET(gtk_builder_get_object(builder, "signup_btn"));
    signup->signup_login = GTK_WIDGET(gtk_builder_get_object(builder, "signup_log"));
    signup->signup_pass1 = GTK_WIDGET(gtk_builder_get_object(builder, "signup_pass1"));
    signup->signup_pass2 = GTK_WIDGET(gtk_builder_get_object(builder, "sighup_pass2"));
    signup->signup_vissible_pass = GTK_WIDGET(gtk_builder_get_object(builder, "signup_show_pass_tick"));
    signup->signup_main_grid = GTK_WIDGET(gtk_builder_get_object(builder, "signup_main_grid"));
    signup->signup_child_box = GTK_WIDGET(gtk_builder_get_object(builder, "signup_child_box"));
}

void mx_init_signin_win(GtkBuilder *builder, t_signin_window *signin) {
    signin->signin_win = GTK_WIDGET(gtk_builder_get_object(builder, "signin_window"));
    if (signin->signin_win == 0)
        fprintf(stderr, "error of open file!\n");
    signin->signin_button = GTK_WIDGET(gtk_builder_get_object(builder, "signin_btn"));
    signin->signin_login = GTK_WIDGET(gtk_builder_get_object(builder, "signin_log"));
    signin->signin_password = GTK_WIDGET(gtk_builder_get_object(builder, "signin_pass"));
    signin->signin_vissible_pass = GTK_WIDGET(gtk_builder_get_object(builder, "signin_show_pass_tick"));
    signin->save_user_tick = GTK_WIDGET(gtk_builder_get_object(builder, "save_user_tick"));
    signin->signin_main_box = GTK_WIDGET(gtk_builder_get_object(builder, "signin_main_grid"));
    signin->signin_child_box = GTK_WIDGET(gtk_builder_get_object(builder, "signin_child_box"));
}

void mx_init_main_chat_win(GtkBuilder *builder, t_main_chat_window *main_chat) {
    main_chat->chat_win = GTK_WIDGET(gtk_builder_get_object(builder, "main_chat_window1"));
    if (main_chat->chat_win == 0)
        fprintf(stderr, "error of open file!\n");
    main_chat->main_chat_box = GTK_WIDGET(gtk_builder_get_object(builder, "main_chat_box1"));
    main_chat->paned_chat = GTK_WIDGET(gtk_builder_get_object(builder, "paned_chat1"));
    main_chat->selected_chat_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "selected_chat_lbl1"));
    main_chat->send_btn = GTK_WIDGET(gtk_builder_get_object(builder, "send_btn1"));
    main_chat->search_line = GTK_WIDGET(gtk_builder_get_object(builder, "search_line1"));
    main_chat->profile_set_btn = GTK_WIDGET(gtk_builder_get_object(builder, "profile_set_btn1"));
    main_chat->chat_line = GTK_WIDGET(gtk_builder_get_object(builder, "text_view_msg"));
    main_chat->search_pan_main_box = GTK_WIDGET(gtk_builder_get_object(builder, "search_pan_main_box"));
    main_chat->chat_entry_split_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_entry_split_box"));
}

void mx_init_objects(GtkBuilder *builder, t_objects *objs) {
    mx_init_signin_win(builder, objs->s_signin_win);
    mx_init_signup_win(builder, objs->s_signup_win);
    mx_init_main_chat_win(builder, objs->chat_win);
}

void mx_set_signin_win_properties(t_signin_window *signin) {
    GdkGeometry hints;
    hints.min_aspect = 1.8;
    hints.max_aspect = 1.8;
    gtk_window_set_geometry_hints(GTK_WINDOW (signin->signin_win), NULL, &hints, GDK_HINT_ASPECT);
    gtk_widget_set_size_request(signin->signin_win, 1350, 750);
}

void mx_set_signup_win_properties(t_signup_window *signup) {
    GdkGeometry hints;
    hints.min_aspect = 1.8;
    hints.max_aspect = 1.8;
    gtk_window_set_geometry_hints(GTK_WINDOW (signup->signup_win), NULL, &hints, GDK_HINT_ASPECT);
    gtk_widget_set_size_request(signup->signup_win, 1350, 750);
}

void mx_set_main_chat_properties(t_main_chat_window *main_chat) {
    GdkGeometry hints;

    // hints.min_aspect = 1.8;
    // hints.max_aspect = 1.8;
    // gtk_window_set_geometry_hints(GTK_WINDOW (main_chat->chat_win), NULL, &hints, GDK_HINT_ASPECT);
    gtk_widget_set_size_request(main_chat->chat_win, 1350, 750);
    gtk_widget_set_size_request(GTK_WIDGET (main_chat->main_chat_box), 1350, 750);
    gtk_paned_set_position(GTK_PANED (main_chat->paned_chat), 171);
}

void mx_set_properties(t_objects *objs) {
    mx_set_signin_win_properties(objs->s_signin_win);
    mx_set_signup_win_properties(objs->s_signup_win);
    mx_set_main_chat_properties(objs->chat_win);
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
