#include "header.h"

static sigset_t set_mask(void) {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    return newmask;
}

static t_server_users *end_work(t_server_users *user) {
    free(user->buff);
    user->buff = 0;
    pthread_mutex_lock(&(user->m_if_work));
    user->work = false;
    pthread_mutex_unlock(&(user->m_if_work));
    return 0;
}

static t_server_users *return_new_work_user(t_server *server_info) {
    t_server_users *user = server_info->works->data;

    mx_pop_front(&(server_info->works));
    return user;
}

void *mx_thread(void *data) {
    sigset_t newmask = set_mask();
    int signo;
    t_server *server_info = data;
    t_server_users *user = 0;

    while (1) {
        sigwait(&(newmask), &signo);
        pthread_mutex_lock(&(server_info->m_works));
        while (server_info->works) {
            user = return_new_work_user(server_info);
            pthread_mutex_unlock(&(server_info->m_works));
            if (user) {
                mx_work_thread(server_info, user);
                user = end_work(user);
            }
            pthread_mutex_lock(&(server_info->m_works));
        }
        pthread_mutex_unlock(&(server_info->m_works));
    }
    return 0;
}