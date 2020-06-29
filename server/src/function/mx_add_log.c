#include "server.h"

void mx_add_log(t_server *server_info, char *msg) {
    pthread_mutex_lock(&(server_info->m_logfile));
    write(server_info->fd_logfile, msg, strlen(msg));
    pthread_mutex_unlock(&(server_info->m_logfile));
}


void mx_add_error_work_log(t_server *server_info, t_server_users *user,
                           char *msg) {
    char log[1024];

     sprintf(log, "%s work ID user = %d, API = %d", 
                msg, user->id_users, user->buff[0]);
    mx_add_log(server_info, log);
}
