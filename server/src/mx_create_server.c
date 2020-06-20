#include "header.h"
#include "mxinet.h"


static t_server *create_malloc(int max_connect, int count_thread) {
    t_server *server_info = malloc(sizeof(t_server));

    if (server_info == 0) {
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        exit(1);
    }
    server_info->poll_set = malloc(sizeof(struct pollfd) * max_connect);
    server_info->table_users = malloc(sizeof(t_server_users) * max_connect);
    server_info->thread = malloc(sizeof(pthread_t) * count_thread);
    server_info->compress_array = false;
    if (server_info->poll_set == 0 || server_info->table_users == 0
        || server_info->thread == 0) {
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        exit(1);
    }
    pthread_rwlock_init(&(server_info->m_edit_database), NULL);
    pthread_rwlock_init(&(server_info->m_edit_users), NULL);
    pthread_mutex_init(&(server_info->m_works), NULL);
    server_info->count_thread = count_thread;
    return server_info;
}

static void set_signal_and_create_thread(t_server *server_info) {
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);

    sigprocmask(SIG_BLOCK, &newmask,0);
    for (int i = 0; i < server_info->count_thread; i++)
        pthread_create(&(server_info->thread[i]), 0, mx_thread, server_info);
}

t_server *mx_create_server(int max_connect, int fd_server, int count_thread) {
    t_server *server_info = create_malloc(max_connect, count_thread);

    server_info->size_connekt = 1;
    server_info->works = 0;
    for (int i = 0; i < max_connect; i++) {
        server_info->poll_set[i].fd = 0;
        server_info->poll_set[i].events = POLLIN;
        server_info->poll_set[i].revents = 0;
        server_info->table_users[i].id_users = 0;
        server_info->table_users[i].socket = 0;
        server_info->table_users[i].work = 0;
        pthread_mutex_init(&(server_info->table_users[i].m_write_socket), NULL);
        pthread_mutex_init(&(server_info->table_users[i].m_if_work), NULL);
    }
    server_info->poll_set[0].fd = fd_server;
    server_info->table_users[0].socket = fd_server;
    set_signal_and_create_thread(server_info);
    return server_info;
}
