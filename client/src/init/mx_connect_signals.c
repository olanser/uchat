/*
* Connect all signals to gtk window
*/
#include "client.h"

void delay(double number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    double milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
}

gboolean mx_glitch(GtkEntry *entry, t_objects *objs) {
    // GtkWidget *broken_screen = gtk_image_new_from_file("/Users/akrasnosel/Desktop/client/client/templates/signin_background.png");
    // GtkWidget *broken_lbl = gtk_image_new_from_file("/Users/akrasnosel/Desktop/client/client/templates/signin_background3.png");

    printf("WHO IS THAT?\n");
    gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->image_name));
    // gtk_image_clear(GTK_IMAGE (objs->s_signin_win->image_name));
    // gtk_image_set_from_file(GTK_IMAGE (objs->s_signin_win->image_name), "/Users/akrasnosel/Desktop/client/client/templates/signin_background.png");
    // delay(0.2);
    gtk_widget_show(GTK_WIDGET (objs->s_signin_win->broken_screen));
    gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_screen));
    gtk_widget_show(GTK_WIDGET (objs->s_signin_win->broken_lbl));
    // delay(5);
    // gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_screen));
    gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_lbl));
    gtk_widget_show(GTK_WIDGET (objs->s_signin_win->image_name));
    // delay(0.1);
    // gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_lbl));
    // gtk_image_set_from_file(GTK_IMAGE (objs->s_signin_win->image_name), "/Users/akrasnosel/Desktop/client/client/templates/signin_background3.png");
    // gtk_image_set_from_file(GTK_IMAGE (objs->s_signin_win->image_name), "/Users/akrasnosel/Desktop/client/client/templates/signin_background1.png");
    // gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->image_name));
    // gtk_layout_put(GTK_LAYOUT (objs->s_signin_win->layout), GTK_WIDGET (broken_screen), 0, 0);
    // delay(0.2);
    // gtk_widget_hide(GTK_WIDGET (broken_screen));
    // gtk_layout_put(GTK_LAYOUT (objs->s_signin_win->layout), GTK_WIDGET (broken_lbl), 0, 0);
    // gtk_widget_hide(GTK_WIDGET (broken_lbl));
    // gtk_widget_show(GTK_WIDGET (objs->s_signin_win->image_name));
    return FALSE;
}

static void connect_to_signin_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "check-resize", (GCallback) mx_resize_signin_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "destroy", (GCallback) mx_destroy_signin_window, NULL);
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_win), "window-state-event", (GCallback) mx_go_fullscreen_signin_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->s_signin_win->signin_button), "clicked", (GCallback) mx_glitch, info->objs);
    // gtk_widget_hide(GTK_WIDGET (info->objs->s_signin_win->broken_screen));
    // gtk_widget_hide(GTK_WIDGET (info->objs->s_signin_win->broken_lbl));

}

static void connect_to_signup_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->s_signup_win->signup_win), "check-resize", (GCallback) mx_resize_signup_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->s_signup_win->signup_win), "destroy", (GCallback) mx_destroy_signup_window, NULL);
}

static void connect_to_main_window(t_info* info) {
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->chat_win), "check-resize", (GCallback) mx_resize_main_window, info->objs);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->chat_win), "destroy", (GCallback) mx_destroy_main_window, NULL);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->send_btn), "clicked", G_CALLBACK(mx_btn_send_msg_clicked), info);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->search_users), "focus-in-event", G_CALLBACK(mx_expand_focus_in), info);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->search_users), "focus-out-event", G_CALLBACK(mx_expand_focus_out), info);
    g_signal_connect(GTK_WIDGET (info->objs->chat_win->search_users), "changed", G_CALLBACK(mx_expand_changed), info);
}

void mx_connect_signals(t_info* info) {
    connect_to_main_window(info);
    connect_to_signin_window(info);
    connect_to_signup_window(info);
    // all signals here
}
