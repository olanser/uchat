#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "libmx.h"

typedef struct s_server_users {
    int socket;
    char *id_users;
    char *buff;
    pthread_mutex_t m_write_socket;
}              t_server_users;


typedef struct s_server {
    int size_connekt;
    pthread_mutex_t m_edit_database;
    pthread_mutex_t m_edit_users;
    struct pollfd *poll_set;
    t_server_users *table_users;
    pthread_mutex_t m_works;
    t_list *works;
    int count_thread;
    pthread_t *thread;
}              t_server;

t_server *mx_create_server(int max_connect, int fd_server, int count_thread);
void *mx_thread(void *data);
int mx_accept_new_connect(t_server *server_info, int max_connect);
int mx_new_data_to_socket(t_server *server_info, int id);

#endif
