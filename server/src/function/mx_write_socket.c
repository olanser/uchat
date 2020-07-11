#include "server.h"

void mx_write_socket(t_server_users *user, char *response) {
    int size = *(int*)&response[5];

    pthread_mutex_lock(&(user->m_write_socket));
    SSL_write(user->ssl, response, size);
    pthread_mutex_unlock(&(user->m_write_socket));
}
