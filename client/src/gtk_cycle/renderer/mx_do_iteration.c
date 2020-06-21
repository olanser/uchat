/*
* Author vbalachevs
* one iteration of cycle
*/
#include "client.h"

void mx_do_iteration(t_info* info) {
    while (gtk_events_pending()) {
        gtk_main_iteration();
    }
}