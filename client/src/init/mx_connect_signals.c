/*
* Connect all signals to gtk window
*/
#include "client.h"

static void connect_to_signin_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "check-resize", (GCallback) mx_resize_signin_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "destroy", (GCallback) mx_destroy_signin_window, NULL);
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "window-state-event", (GCallback) mx_go_fullscreen_signin_window, info->objs);
}

static void connect_to_signup_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->s_signup_win->signup_win), "check-resize", (GCallback) mx_resize_signup_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->s_signup_win->signup_win), "destroy", (GCallback) mx_destroy_signup_window, NULL);
}

static void connect_to_main_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->chat_win), "check-resize", (GCallback) mx_resize_main_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->chat_win), "destroy", (GCallback) mx_destroy_main_window, NULL);
}

void mx_connect_signals(t_info* info) {
    connect_to_main_window(info);
    connect_to_signin_window(info);
    connect_to_signup_window(info);
    // all signals here
}
