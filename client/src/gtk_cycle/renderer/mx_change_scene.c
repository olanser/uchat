/* 
* Author vbalachevs
* change current scene
*/
#include "client.h"
#include "defines_client.h"

// static void resize(t_objects *objs) {
//     GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(objs->s_signin_win->signin_win));
//     int height = gdk_window_get_height(gdk_window);
//     int width = gdk_window_get_width(gdk_window);

//     printf("height = %d and width = %d\n", height, width);
// }

static void show_signin(t_objects *objs) {
    gtk_widget_show(objs->s_signin_win->signin_win);
    gtk_widget_hide(objs->chat_win->chat_win);
    gtk_widget_hide(objs->s_signup_win->signup_win);
    // resize(objs);
}

static void show_chat(t_objects *objs) {
    gtk_widget_show(objs->chat_win->chat_win);
    gtk_widget_hide(objs->s_signin_win->signin_win);
    gtk_widget_hide(objs->s_signup_win->signup_win);
}

static void show_signup(t_objects *objs) {
    gtk_widget_show(objs->s_signup_win->signup_win);
    gtk_widget_hide(objs->s_signin_win->signin_win);
    gtk_widget_hide(objs->chat_win->chat_win);
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
