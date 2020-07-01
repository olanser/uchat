/* 
* author vbalachevs
* Moving and drawing object
*/
#include "mxdraw.h"

void mx_paly_object(GtkLayout *layout, t_dr_obj *obj, int cycle) {
    t_anim *anim = obj->anim;
    t_movable mov = obj->movable;

    mx_move_obj(obj);
    // draw only showable
    if (cycle % anim->anim_time == 0) {
        gtk_widget_hide(anim->images[anim->current_sprite]);
        anim->current_sprite++;
        if (anim->current_sprite >= anim->count_sprites) {
            anim->current_sprite = 0;
        }
        gtk_widget_show(anim->images[anim->current_sprite]);
    }
    gtk_layout_move(layout, anim->images[anim->current_sprite], mov.pos.x, mov.pos.y);
}
