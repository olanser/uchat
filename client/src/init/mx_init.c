/*
* Author vbalachevs
* Initialize all components of program
*/
#include "client.h"
#include "mxinet.h"
#include "defines.h"
#include "libmx.h"
#include "mxdraw.h"

void mx_init_info(t_info **info) {
    *info = malloc(sizeof(t_info));
    (*info)->sock = 0;
    (*info)->scene = 0;
    (*info)->objs = malloc(sizeof(t_objects));
    (*info)->objs->s_signin_win = malloc(sizeof(t_signin_window));
    (*info)->objs->s_signup_win = malloc(sizeof(t_signup_window));
    (*info)->objs->chat_win = malloc(sizeof(t_main_chat_window));
    (*info)->id_chat = 1;
    (*info)->list_of_chats = 0;
    (*info)->user_info = 0;
}

t_pacman *get_pacman(t_info *info) {
    t_pacman* pacman = malloc(sizeof(t_pacman));
    t_movable mov = {100, 100, 2, 0};
    const char *sprites[] = {MX_PAC_SP1, MX_PAC_SP2};
    pacman->draw_obj = mx_create_drobject(mov, sprites, 2, MX_PACMAN_ANIM_DUR);
    mx_put_obj(GTK_LAYOUT(info->objs->chat_win->layout_main), pacman->draw_obj);
    return pacman;
}

void mx_init_characters(t_info *info) {
    info->chars = malloc(sizeof(t_characters));
    info->chars->pacman = get_pacman(info);
}

void mx_init(t_info **info) {
    pthread_t th_listener;
    mx_init_info(info);
    mx_connect(*info);
    pthread_create(&th_listener, 0, mx_listener, *info);
    mx_init_gtk(*info);
    mx_init_characters(*info);
    mx_chang_scene(*info, MX_SCENE_MAIN_CHAT);
    // mx_chang_scene(*info, MX_SCENE_SIGNUP);
    // mx_chang_scene(*info, MX_SCENE_SIGNIN);
}

// void mx_show_window() {
//     mx_show();
// } 
