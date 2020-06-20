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

// void mx_connect(t_info *info) {
//     info->sock = mx_create_tcp_csock(2365, INADDR_LOOPBACK);
// }



void mx_init(t_info **info) {
    mx_init_info(info);
    // mx_connect(info);
    mx_init_gtk(*info);
    mx_chang_scene(*info, MX_SCENE_MAIN);
} 

// void mx_show_window() {
//     mx_show();
// } 