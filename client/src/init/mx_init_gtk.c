/* 
* Author vbalachevs
* load all objects an signals from builder
*/
#include "client.h"
#include "defines_client.h"

static void place_label_signup(t_signup_window *signup) {
    GdkPixbuf *pixbuf;

    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_CHAT_NAME1, 540, 300, NULL);
    signup->image_name = gtk_image_new_from_pixbuf(pixbuf);
    gtk_layout_put(
        GTK_LAYOUT(signup->layout), GTK_WIDGET (signup->image_name), 0, 0);
}

void mx_init_signup_win(GtkBuilder *builder, t_signup_window *signup) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(
                            MX_INVIS_ICON_W, 30, 30, NULL);

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
    signup->layout = mx_build_get(builder, "signup_layout");
    place_label_signup(signup);
}

static void place_label_signin(t_signin_window *signin) {
    GdkPixbuf *pixbuf;

    pixbuf = gdk_pixbuf_new_from_file_at_size(MX_CHAT_NAME1, 540, 300, NULL);
    signin->image_name = gtk_image_new_from_pixbuf(pixbuf);
    gtk_layout_put(
        GTK_LAYOUT(signin->layout), GTK_WIDGET (signin->image_name), 0, 0);
}

void mx_init_signin_win(GtkBuilder *builder, t_signin_window *signin) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size(
        MX_INVIS_ICON_W, 30, 30, NULL);

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
    signin->go_to_signup = mx_build_get(builder, "go_to_signup");
    place_label_signin(signin);
}

void mx_init_gtk(t_info* info) {
    mx_connect_css();
    mx_connect_builder(info);
    mx_connect_signals(info);
}
