/*
* Author vbalachevs
* Initialize all components of program
*/
#include "client.h"
#include "mxinet.h"
#include "defines.h"

void mx_init_info(t_info **info) {
    *info = malloc(sizeof(t_info));
    (*info)->sock = 0;
    (*info)->scene = 0;
    (*info)->objs = malloc(sizeof(t_objects));
    (*info)->objs->s_main_win = malloc(sizeof(t_main_window));
}

void mx_init(t_info **info) {
    // pthread_t th_listener;
    // pthread_create(&th_listener, 0, mx_listener, *info);
    mx_init_info(info);
    mx_connect(*info);
    mx_init_gtk(*info);
    mx_chang_scene(*info, MX_SCENE_MAIN);
}
