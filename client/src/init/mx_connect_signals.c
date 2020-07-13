/*
* Connect all signals to gtk window
*/
#include "client.h"

void delay(double number_of_seconds) { 
    double milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 

    while (clock() < start_time + milli_seconds);
}

static void connect_to_signin_window(t_info* info) {
    t_signin_window *win = info->objs->s_signin_win;

    g_signal_connect(
        GTK_WIDGET(win->signin_win),
        "check-resize", (GCallback)mx_resize_signin_window, info->objs);
    g_signal_connect(
        GTK_WIDGET(win->signin_win), "destroy",
        (GCallback)mx_destroy_signin_window, NULL);
    g_signal_connect(
        GTK_WIDGET(win->signin_win), "window-state-event",
        (GCallback)mx_go_fullscreen_signin_window, info->objs);
    g_signal_connect(GTK_WIDGET(win->signin_button), "clicked",
        (GCallback)mx_btn_signin, info);
    g_signal_connect(
        GTK_WIDGET(win->signin_win), "key-press-event",
        (GCallback)mx_key_press_signin, info);
    g_signal_connect(
        GTK_WIDGET (win->signin_vissible_pass), "clicked",
        (GCallback)mx_vis_pass_signin, info);
}

static void connect_to_signup_window(t_info* info) {
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->signup_win),
        "check-resize", (GCallback)mx_resize_signup_window, info->objs);
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->signup_win), "destroy",
        (GCallback)mx_destroy_signup_window, NULL);
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->signup_buton), "clicked",
        (GCallback)mx_btn_signup, info);
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->signup_win), "key-press-event",
        (GCallback)mx_key_press_signup, info);
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->btn_go_to_signin), "clicked",
        (GCallback)mx_btn_go_to_signin, info);
    g_signal_connect(
        GTK_WIDGET(info->objs->s_signup_win->signup_vissible_pass), "clicked",
        (GCallback)mx_vis_pass, info);
}

static void conect2(t_info* info) {
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->search_users), "changed",
        G_CALLBACK(mx_expand_changed), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->btn_choose_file), "clicked",
        G_CALLBACK(mx_btn_choose_file), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->btn_show_sticker), "clicked",
        G_CALLBACK(mx_btn_show_stickers), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->btn_logout), "clicked",
        G_CALLBACK(mx_btn_exit), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->btn_settings), "clicked",
        G_CALLBACK(mx_btn_settings), info);
}

static void connect_to_main_window(t_info* info) {
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->chat_win), "check-resize",
        (GCallback) mx_resize_main_window, info->objs);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->chat_win), "destroy",
        (GCallback) mx_destroy_main_window, NULL);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->send_btn), "clicked",
        G_CALLBACK(mx_btn_send_msg_clicked), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->search_users), "focus-in-event",
        G_CALLBACK(mx_expand_focus_in), info);
    g_signal_connect(
        GTK_WIDGET (info->objs->chat_win->search_users), "focus-out-event",
        G_CALLBACK(mx_expand_focus_out), info);
    conect2(info);
}

void mx_connect_signals(t_info* info) {
    connect_to_main_window(info);
    connect_to_signin_window(info);
    connect_to_signup_window(info);
}
