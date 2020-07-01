/* 
* author vbalachevs
* Creating movable object 
* uses for get and set coordinate of object
* and vector(direction) of moving
*/
#include "mxdraw.h"

t_movable mx_crerate_movable(t_vec2 pos, t_vec2 mov) {
    t_movable movable;
    movable.pos = pos;
    movable.mov = mov;
    return movable;
}
