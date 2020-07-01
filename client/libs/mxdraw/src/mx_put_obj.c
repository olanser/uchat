/* 
* author vbalachevs
* Put animation on layout
*/
#include "mxdraw.h"

void mx_put_obj(GtkLayout* layout, t_dr_obj *obj) {
    for (int i = 0; i < obj->anim->count_sprites; i++)
        gtk_layout_put(layout, obj->anim->images[i], obj->movable.pos.x, obj->movable.pos.y);
}
