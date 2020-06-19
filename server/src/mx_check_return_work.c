#include "header.h"
#include "mxinet.h"

void mx_check_return_work(t_server *server_info) {
    pthread_mutex_lock(&(server_info->m_list_fd_socket));
    while (server_info->list_fd_socket) {
        for (int i = 1; i < server_info->size_connekt; i++) {
            if (*((int*)server_info->list_fd_socket->data) == server_info->poll_set[i].fd) {
                server_info->poll_set[i].events = POLLIN;
                server_info->poll_set[i].revents = 0;
                break;
            }
        }
        mx_pop_front_free_data(&(server_info->list_fd_socket));
    }
    pthread_mutex_unlock(&(server_info->m_list_fd_socket));
}
