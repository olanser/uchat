#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sqlite3.h>
#include "libmx.h"
#include "mxinet.h"

typedef struct s_server_users {
    int socket;
    char *id_users;
    char *buff;
    bool work;
    pthread_mutex_t m_if_work;
    pthread_mutex_t m_write_socket;
}              t_server_users;


typedef struct s_server {
    int size_connekt;
    pthread_rwlock_t m_edit_database;
    sqlite3 *db;
    pthread_rwlock_t m_edit_users;
    t_server_users *table_users;
    struct pollfd *poll_set;
    pthread_mutex_t m_works;
    t_list *works;
    int count_thread;
    pthread_t *thread;
    bool compress_array;
}              t_server;

t_server *mx_create_server(int max_connect, int fd_server, int count_thread);
void *mx_thread(void *data);
int mx_accept_new_connect(t_server *server_info, int max_connect);
int mx_new_data_to_socket(t_server *server_info, int id);
void mx_compress_array(t_server *server_info);
bool mx_check_not_work(t_server_users user);
void mx_work_thread(t_server *server_info, t_server_users *user);
char *mx_create_response(char id_request, int query, char status);
char *mx_do_request(t_server *server_info, t_server_users *user);
void mx_write_socket(int fd, char *response);

//API
char *mx_signup(t_server *server_info, t_server_users *user);
char *mx_signin(t_server *server_info, t_server_users *user);
char *mx_send_message(t_server *server_info, t_server_users *user);

#endif
