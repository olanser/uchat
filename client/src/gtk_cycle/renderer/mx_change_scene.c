/* 
* Author vbalachevs
* change current scene
*/
#include "client.h"
#include "defines.h"

// static void resize(t_objects *objs) {
//     GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->s_signin_win->signin_win));
//     int height = gdk_window_get_height(gdk_window);
//     int width = gdk_window_get_width(gdk_window);

//     printf("height = %d and width = %d\n", height, width);
// }

static void show_signin(t_objects *objs) {
    gtk_widget_show_all(objs->s_signin_win->signin_win);
    gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_screen));
    gtk_widget_hide(GTK_WIDGET (objs->s_signin_win->broken_lbl));
    // resize(objs);
}

// static void resize_main_box(t_main_chat_window *main_chat) {
//     GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(main_chat->chat_win));
//     int height = gdk_window_get_height(gdk_window);
//     int width = gdk_window_get_width(gdk_window);

//     printf("height = %d and width = %d\n", height, width);
// }

static void show_chat(t_objects *objs) {
    gtk_widget_show_all(objs->chat_win->chat_win);
    // resize_main_box(objs->chat_win);
}

static void show_signup(t_objects *objs) {
    gtk_widget_show_all(objs->s_signup_win->signup_win);
}

int mx_chang_scene(t_info *info, int scene) {
    info->scene = scene;
    if (info->scene == MX_SCENE_SIGNIN) {
        show_signin(info->objs);
    }
    else if (info->scene == MX_SCENE_MAIN_CHAT) {
        show_chat(info->objs);
    }
    else if (info->scene == MX_SCENE_SIGNUP) {
        show_signup(info->objs);
    }
    return 0;
}
