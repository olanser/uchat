#include "client.h"
#include "defines_client.h"

gboolean mx_key_press_signup(GtkWidget*widget, GdkEvent *event, t_info *info) {
    if (event->key.state == 1 && event->key.keyval == 65361) {
        mx_chang_scene(info, MX_SCENE_SIGNIN);
    }
    return FALSE;
}