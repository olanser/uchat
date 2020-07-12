#include "client.h"

gboolean mx_scene_cycle(void *data) {
    clock_t time = clock();
    t_info *info = (t_info*)data;
    static int cycle = 0;
    t_anim *anim = info->chars->pacman->draw_obj->anim;
    t_movable mov = info->chars->pacman->draw_obj->movable;

    mx_paly_object(GTK_LAYOUT(info->objs->chat_win->layout_main),
                   info->chars->pacman->draw_obj, cycle);
    cycle++;
    return TRUE;
}
