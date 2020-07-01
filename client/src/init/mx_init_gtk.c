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

static void place_label(t_signin_window *signin) {
    signin->image_name = gtk_image_new_from_file("/Users/akrasnosel/Desktop/client/client/templates/signin_background1.png");
    signin->broken_screen = gtk_image_new_from_file("/Users/akrasnosel/Desktop/client/client/templates/signin_background.png");
    signin->broken_lbl = gtk_image_new_from_file("/Users/akrasnosel/Desktop/client/client/templates/signin_background3.png");
    gtk_layout_put(GTK_LAYOUT (signin->layout), GTK_WIDGET (signin->image_name), 0, 0);
    gtk_layout_put(GTK_LAYOUT (signin->layout), GTK_WIDGET (signin->broken_screen), 0, 0);
    gtk_layout_put(GTK_LAYOUT (signin->layout), GTK_WIDGET (signin->broken_lbl), 0, 0);
    // gtk_widget_hide(GTK_WIDGET (signin->broken_screen));
    // gtk_widget_hide(GTK_WIDGET (signin->broken_lbl));
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
    signin->layout = GTK_WIDGET(gtk_builder_get_object(builder, "signin_layout"));
    place_label(signin);
}

GtkWidget* get_user_widget() {
    GtkWidget *widget = gtk_event_box_new();
    GtkWidget *label = gtk_label_new(")");

    gtk_container_add(GTK_CONTAINER(widget), label);
    gtk_widget_show(label);
    return widget;
}

void mx_init_search_user(GtkBuilder *builder, t_main_chat_window *main_chat, t_info*info) {
    main_chat->search_users = GTK_WIDGET(gtk_builder_get_object(builder, "search_users"));
    main_chat->list_box_users = gtk_list_box_new();
    gtk_list_box_insert(GTK_LIST_BOX(main_chat->listbox_search), main_chat->list_box_users, -1);
    main_chat->user_widgets = malloc(sizeof(GtkWidget*) * 10);
    for (int i = 0; i < 10; i++) {
        main_chat->user_widgets[i] = get_user_widget();
        t_user_info* user_info = malloc(sizeof(t_user_info));
        user_info->id = 0;
        g_object_set_data(G_OBJECT(main_chat->user_widgets[i]), "user_info", user_info);
        gtk_list_box_insert(GTK_LIST_BOX(main_chat->list_box_users), main_chat->user_widgets[i], -1);
        g_signal_connect(GTK_WIDGET(main_chat->user_widgets[i]), "button-press-event", G_CALLBACK(mx_expand_user_click), info);
        // gtk_widget_show(user_widget);
    }
    gtk_widget_hide(main_chat->list_box_users);
    gtk_widget_show(main_chat->search_users);
}

void mx_init_main_chat_win(GtkBuilder *builder, t_main_chat_window *main_chat, t_info *info) {
    main_chat->chat_win = GTK_WIDGET(gtk_builder_get_object(builder, "main_chat_window1"));
    if (main_chat->chat_win == 0)
        fprintf(stderr, "error of open file!\n");
    main_chat->main_chat_box = GTK_WIDGET(gtk_builder_get_object(builder, "main_chat_box1"));
    main_chat->paned_chat = GTK_WIDGET(gtk_builder_get_object(builder, "paned_chat1"));
    main_chat->selected_chat_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "selected_chat_lbl1"));
    main_chat->send_btn = GTK_WIDGET(gtk_builder_get_object(builder, "send_btn"));
    main_chat->search_line = GTK_WIDGET(gtk_builder_get_object(builder, "search_line1"));
    main_chat->profile_set_btn = GTK_WIDGET(gtk_builder_get_object(builder, "profile_set_btn1"));
    main_chat->chat_line = GTK_WIDGET(gtk_builder_get_object(builder, "text_view_msg"));
    main_chat->search_pan_main_box = GTK_WIDGET(gtk_builder_get_object(builder, "search_pan_main_box"));
    main_chat->chat_entry_split_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_entry_split_box"));
    main_chat->listbox_search = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_search"));
    main_chat->search_viewport1 = GTK_WIDGET(gtk_builder_get_object(builder, "search_viewport1"));
    main_chat->notebook = GTK_WIDGET(gtk_builder_get_object(builder, "notebook"));
    gtk_widget_show_all(main_chat->chat_win);
    mx_init_search_user(builder, main_chat, info);
    
}

void mx_init_objects(GtkBuilder *builder, t_objects *objs, t_info*info) {
    mx_init_signin_win(builder, objs->s_signin_win);
    mx_init_signup_win(builder, objs->s_signup_win);
    mx_init_main_chat_win(builder, objs->chat_win, info);
}

void mx_set_signin_win_properties(t_signin_window *signin) {
    gtk_widget_set_size_request(signin->signin_win, 1350, 750);
}

void mx_set_signup_win_properties(t_signup_window *signup) {
    gtk_widget_set_size_request(signup->signup_win, 540, 300);
}

void mx_set_main_chat_properties(t_main_chat_window *main_chat) {
    gtk_widget_set_size_request(main_chat->chat_win, 540, 300);
    gtk_widget_set_size_request(GTK_WIDGET (main_chat->main_chat_box), 540, 300);
    gtk_paned_set_position(GTK_PANED (main_chat->paned_chat), 171);
}

void mx_set_properties(t_objects *objs) {
    mx_set_signin_win_properties(objs->s_signin_win);
    mx_set_signup_win_properties(objs->s_signup_win);
    mx_set_main_chat_properties(objs->chat_win);
}

void mx_connect_builder(t_info* info) {
    GtkBuilder* builder = gtk_builder_new_from_file(MX_PATH_TO_TEMPLATE);
    mx_init_objects(builder, info->objs, info);
    mx_set_properties(info->objs);
}

// void mx_connect_css(void) {
//     GtkCssProvider *provider = gtk_css_provider_new();
//     gtk_css_provider_load_from_path(provider, SIGNIN_CSS_STYLE, NULL);
//         gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
//                                GTK_STYLE_PROVIDER(provider),
//                                GTK_STYLE_PROVIDER_PRIORITY_USER);
// }

void mx_init_gtk(t_info* info) {
    // mx_connect_css();
    mx_connect_builder(info);
    mx_connect_signals(info);
}
