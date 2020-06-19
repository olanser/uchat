#include "header.h"

static sigset_t set_mask(void) {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    return newmask;
}

void *mx_thread(void *data) {
    sigset_t newmask = set_mask();
    int signo;
    t_server *server_info = data;
    t_server_users *user = 0;

    while (1) {
        sigwait(&(newmask), &signo);
        printf("yes\n");
        user = 0;
        pthread_mutex_lock(&(server_info->m_works));
        if (server_info->works) {
            user = server_info->works->data;
            mx_pop_front(&(server_info->works));
        }
        else {
            fprintf(stderr, "ERROR thread not work\n");
        }
        pthread_mutex_unlock(&(server_info->m_works));
        if (user) {
            char comand = user->buff[0];
            int size = *((int*)&(user->buff[5]));
            printf("Comand id = %d and size = %d\n", comand, size);
            free(user->buff);
            user->buff = 0;
            pthread_mutex_lock(&(server_info->m_list_fd_socket));
            int *test = malloc(sizeof(int));
            *test = user->socket;
            mx_push_front(&(server_info->list_fd_socket), test);
            pthread_mutex_unlock(&(server_info->m_list_fd_socket));
        }
        int a = 1;
        for (int i = 0; i < 223242342; i++)
            a *= i;
        pthread_mutex_lock(&(server_info->m_works));
        if (server_info->works) {
            kill(getpid(), SIGUSR1);
        }
        pthread_mutex_unlock(&(server_info->m_works));
    }
    return 0;
}