#include "client.h"

int mx_send_msg_(int socket, char *buff, int size, t_info *info) {
    int count = 0;
    
    pthread_mutex_lock(&info->m_write_sock);
    count = write(socket, buff, size);
    pthread_mutex_unlock(&info->m_write_sock);
    return count;
}
