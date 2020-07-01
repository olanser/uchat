/* 
* author vbalachevs
* Drawing all characters on screen
* and changing animation
*/
#include "mxdraw.h"

void mx_draw_anim(int cycle, t_anim *anim) {
    if (cycle % anim->anim_time == 0) {
        gtk_widget_hide(anim->images[anim->current_sprite]);
        anim->current_sprite++;
        if (anim->current_sprite >= anim->count_sprites) {
            anim->current_sprite = 0;
        }
        gtk_widget_show(anim->images[anim->current_sprite]);
    }
}
