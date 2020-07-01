/* 
* author vbalachevs
* Creating drawing object 
* with animation and movable objects
*/
#include "mxdraw.h"

t_dr_obj* mx_create_drobject(
    t_movable movable,
    const char** imgs,
    int count_sprites,
    int duration) 
{
    t_dr_obj *new_obj = malloc(sizeof(t_dr_obj));
    new_obj->anim = mx_create_anim(imgs, count_sprites, duration);
    new_obj->movable = movable;
    return new_obj;
}
