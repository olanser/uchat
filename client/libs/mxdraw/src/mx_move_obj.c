/* 
* author vbalachevs
* Change coordinates of object
*/

#include "mxdraw.h"

void mx_move_obj(t_dr_obj *obj) {
    obj->movable.pos.x += obj->movable.mov.x;
    obj->movable.pos.y += obj->movable.mov.y;
}
