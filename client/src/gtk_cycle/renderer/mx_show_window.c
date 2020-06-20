/* 
* Author vbalachevs
* cycle for show window
*/
#include "client.h"
#include "defines.h"

void mx_show_window(t_info* info) {
    while(1) {
        mx_do_iteration(info);
    }
}
