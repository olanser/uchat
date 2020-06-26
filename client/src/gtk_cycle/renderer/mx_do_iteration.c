/*
* Author vbalachevs
* one iteration of cycle
*/
#include "client.h"
#include "defines.h"

static void resize_main_box(t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->chat_win->chat_win));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);
    int position = gtk_paned_get_position(GTK_PANED (objs->chat_win->paned_chat));
        // printf("height = %d and width = %d, divider position is on %d\n", height, width, position);
        gtk_widget_set_size_request(GTK_WIDGET (objs->chat_win->main_chat_box), width, height);
}

static void resize_signin_window(t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->s_signin_win->signin_win));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    // printf("height = %d and width = %d\n", height, width);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_main_box), width, height);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signin_win->signin_child_box), width, height);
}

static void resize_signup_window (t_objects *objs) {
    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->s_signup_win->signup_win));
    int height = gdk_window_get_height(gdk_window);
    int width = gdk_window_get_width(gdk_window);

    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signup_win->signup_main_grid), width, height);
    gtk_widget_set_size_request(GTK_WIDGET (objs->s_signup_win->signup_child_box), width, height);
}

void mx_resize_widgets(t_info* info) {
    if (info->scene == MX_SCENE_MAIN_CHAT) {
        // printf("MAIN CHAT WINDOW\n");
        resize_main_box(info->objs);
    }
    else if (info->scene == MX_SCENE_SIGNIN) {
        // printf("SIGNIN WINDOW\n");
        resize_signin_window(info->objs);
    }
    else if (info->scene == MX_SCENE_SIGNUP) {
        // printf("SIGNUP WINDOW\n");
        resize_signup_window(info->objs);
    }
}

void mx_do_iteration(t_info* info) {
    // while (gtk_events_pending()) {
        mx_resize_widgets(info);
        // resize(info->objs);
        gtk_main_iteration();
    // }
}
