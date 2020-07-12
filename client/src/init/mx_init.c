/*
* Author vbalachevs
* Initialize all components of program
*/
#include "client.h"
#include "mxinet.h"
#include "defines_client.h"
#include "libmx.h"
#include "mxdraw.h"

static void init_mem(t_info **info) {
    (*info)->objs = malloc(sizeof(t_objects));
    (*info)->objs->s_signin_win = malloc(sizeof(t_signin_window));
    (*info)->objs->s_signup_win = malloc(sizeof(t_signup_window));
    (*info)->objs->chat_win = malloc(sizeof(t_main_chat_window));
    (*info)->objs->s_win_profile = malloc(sizeof(t_win_profile));
    (*info)->objs->chat_win->size = malloc(sizeof(t_win_size));
    pthread_mutex_init(&(*info)->m_file_list, 0);
    pthread_mutex_init(&(*info)->m_write_sock, 0);
    pthread_mutex_init(&(*info)->m_file_recv_list, 0);
}

void mx_init_info(t_info **info) {
    *info = malloc(sizeof(t_info));
    (*info)->sock = 0;
    (*info)->scene = 0;
    init_mem(info);
    (*info)->objs->chat_win->size->position = 171;
    (*info)->objs->chat_win->size->height = 750;
    (*info)->objs->chat_win->size->width = 1350;
    (*info)->id_chat = 1;
    (*info)->list_of_chats = 0;
    (*info)->list_of_files = 0;
    (*info)->user_info = 0;
    (*info)->id_of_editing_msg = 0;
    (*info)->id_of_editing_chat = 0;
    (*info)->list_of_recv_files = 0;
}

t_pacman *get_pacman(t_info *info) {
    t_pacman* pacman = malloc(sizeof(t_pacman));
    t_movable mov = {100, 100, 2, 0};
    const char *sprites[] = {MX_PAC_SP1, MX_PAC_SP2};

    pacman->draw_obj = mx_create_drobject(mov, sprites, 2, MX_PACMAN_ANIM_DUR);
    mx_put_obj(GTK_LAYOUT(info->objs->chat_win->layout_main), 
               pacman->draw_obj);
    return pacman;
}

void mx_init_signals() {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &newmask, 0);
}

void mx_init(t_info **info, int argc, char **argv) {
    pthread_t th_listener;
    pthread_t th_sender;

    mx_init_signals();
    mx_init_info(info);
    mx_connect(*info, argc, argv);
    pthread_create(&th_listener, 0, mx_listener, *info);
    pthread_create(&th_sender, 0, mx_thread_send_file, *info);
    mx_init_gtk(*info);
}

