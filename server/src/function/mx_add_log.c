#include "server.h"

void mx_add_log(t_server *server_info, char *msg) {
    pthread_mutex_lock(&(server_info->m_logfile));
    write(server_info->fd_logfile, msg, strlen(msg));
    pthread_mutex_unlock(&(server_info->m_logfile));
}
