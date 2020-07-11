#include "client.h"
#include "defines_client.h"

gboolean mx_key_press_signin(GtkWidget*widget, GdkEvent *event, t_info *info) {
    if (event->key.state == 1 && event->key.keyval == 65363) {
        mx_chang_scene(info, MX_SCENE_SIGNUP);
    }
    return FALSE;
}