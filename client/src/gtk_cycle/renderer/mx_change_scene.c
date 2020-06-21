/* 
* Author vbalachevs
* change current scene
*/
#include "client.h"
#include "defines.h"

static void show_main(t_objects *objs) {
    gtk_widget_show_all(objs->s_main_win->wid_main_win);
    // and hide all others
}

int mx_chang_scene(t_info *info, int scene) {
    info->scene = scene;
    if (info->scene == MX_SCENE_MAIN) {
        show_main(info->objs);
    }
    return 0;
}
