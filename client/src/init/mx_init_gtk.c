/* 
* Author vbalachevs
* load all objects an signals from builder
*/
#include "client.h"
#include "defines_client.h"

void mx_init_signup_win(GtkBuilder *builder, t_signup_window *signup) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(MX_INVIS_ICON_W, 30, 30, NULL);

    memset(&signup->vis, 0, sizeof(bool));
    signup->signup_win = mx_build_get(builder, "signup_window");
    if (signup->signup_win == 0)
        fprintf(stderr, "error of open file!\n");
    signup->signup_buton = mx_build_get(builder, "signup_btn");
    signup->signup_login = mx_build_get(builder, "signup_log");
    signup->signup_pass1 = mx_build_get(builder, "signup_pass1");
    signup->signup_pass2 = mx_build_get(builder, "signup_pass2");
    signup->vis_img = mx_build_get(builder, "image7");
    signup->signup_vissible_pass = mx_build_get(
        builder, "signup_show_pass_tick");
    gtk_image_set_from_pixbuf(GTK_IMAGE (signup->vis_img), pixbuf);
    signup->signup_main_grid = mx_build_get(builder, "signup_main_grid");
    signup->signup_child_box = mx_build_get(builder, "signup_child_box");
    signup->btn_go_to_signin = mx_build_get(builder, "btn_go_to_signin");
}

static void place_label(t_signin_window *signin) {
    signin->image_name = gtk_image_new_from_file(
        "templates/signin_background1.png");
    signin->broken_screen = gtk_image_new_from_file(
        "templates/signin_background.png");
    signin->broken_lbl = gtk_image_new_from_file(
        "templates/signin_background3.png");
    gtk_layout_put(
        GTK_LAYOUT(signin->layout), GTK_WIDGET (signin->image_name), 0, 0);
    gtk_layout_put(
        GTK_LAYOUT(signin->layout), GTK_WIDGET (signin->broken_screen), 0, 0);
    gtk_layout_put(
        GTK_LAYOUT(signin->layout), GTK_WIDGET (signin->broken_lbl), 0, 0);
}

void mx_init_signin_win(GtkBuilder *builder, t_signin_window *signin) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(MX_INVIS_ICON_W, 30, 30, NULL);

    memset(&signin->vis, 0, sizeof(bool));
    signin->signin_win = mx_build_get(builder, "signin_window");
    if (signin->signin_win == 0)
        fprintf(stderr, "error of open file!\n");
    signin->signin_button = mx_build_get(builder, "signin_btn");
    signin->signin_login = mx_build_get(builder, "signin_log");
    signin->signin_password = mx_build_get(builder, "signin_pass");
    signin->vis_img = mx_build_get(builder, "image8");
    signin->signin_vissible_pass = mx_build_get(
        builder, "signin_show_pass_tick");
    gtk_image_set_from_pixbuf(GTK_IMAGE (signin->vis_img), pixbuf);
    signin->save_user_tick = mx_build_get(builder, "save_user_tick");
    signin->signin_main_box = mx_build_get(builder, "signin_main_grid");
    signin->signin_child_box = mx_build_get(builder, "signin_child_box");
    signin->layout = mx_build_get(builder, "signin_layout");
    place_label(signin);
}

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



void mx_connect_builder(t_info* info) {
    GtkBuilder* builder = gtk_builder_new_from_file(MX_PATH_TO_TEMPLATE);
    mx_init_objects(builder, info->objs, info);
    mx_set_properties(info->objs);
    mx_init_profile(info);
}

void mx_connect_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(provider, MX_CSS_MAIN_STYLES, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void mx_init_gtk(t_info* info) {
    mx_connect_css();
    mx_connect_builder(info);
    mx_connect_signals(info);
}
