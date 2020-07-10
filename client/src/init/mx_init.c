/*
* Author vbalachevs
* Initialize all components of program
*/
#include "client.h"
#include "mxinet.h"
#include "defines_client.h"
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
    (*info)->objs->s_win_profile = malloc(sizeof(t_win_profile));
    (*info)->id_chat = 1;
    (*info)->list_of_chats = 0;
    (*info)->list_of_files = 0;
    (*info)->user_info = 0;
    (*info)->id_of_editing_msg = 0;
    (*info)->id_of_editing_chat = 0;
    (*info)->list_of_recv_files = 0;
    pthread_mutex_init(&(*info)->m_file_list, 0);
    pthread_mutex_init(&(*info)->m_write_sock, 0);
    pthread_mutex_init(&(*info)->m_file_recv_list, 0);
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

void mx_init_signals() {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1); // new file sending
    sigprocmask(SIG_BLOCK, &newmask, 0);
}
void mx_init(t_info **info) {
    pthread_t th_listener;
    pthread_t th_sender;

    mx_init_signals();
    mx_init_info(info);
    mx_connect(*info);
    pthread_create(&th_listener, 0, mx_listener, *info);
    pthread_create(&th_sender, 0, mx_thread_send_file, *info);
    mx_init_gtk(*info);
    // mx_init_characters(*info);
    // mx_chang_scene(*info, MX_SCENE_MAIN_CHAT);
    // mx_chang_scene(*info, MX_SCENE_SIGNUP);
    // mx_chang_scene(*info, MX_SCENE_SIGNIN);
}

