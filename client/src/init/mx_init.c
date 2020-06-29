/*
* Author vbalachevs
* Initialize all components of program
*/
#include "client.h"
#include "mxinet.h"
#include "defines.h"
#include "libmx.h"

void mx_init_info(t_info **info) {
    *info = malloc(sizeof(t_info));
    (*info)->sock = 0;
    (*info)->scene = 0;
    (*info)->objs = malloc(sizeof(t_objects));
    (*info)->objs->s_signin_win = malloc(sizeof(t_signin_window));
    (*info)->objs->s_signup_win = malloc(sizeof(t_signup_window));
    (*info)->objs->chat_win = malloc(sizeof(t_main_chat_window));
    (*info)->id_chat = mx_strdup("1");
    (*info)->list_of_chats = 0;
    pthread_mutex_init(&(*info)->m_editing_gtk, NULL);
}

void mx_init(t_info **info) {
    pthread_t th_listener;
    mx_init_info(info);
    mx_connect(*info);
    pthread_create(&th_listener, 0, mx_listener, *info);
    mx_init_gtk(*info);
    mx_chang_scene(*info, MX_SCENE_MAIN_CHAT);
    // mx_chang_scene(*info, MX_SCENE_SIGNIN);
}

// void mx_show_window() {
//     mx_show();
// } 
