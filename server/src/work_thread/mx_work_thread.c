#include "header.h"

void mx_work_thread(t_server *server_info, t_server_users *user) {
    char comand = user->buff[0];
    int size = *((int*)&(user->buff[5]));
    // printf("Comand id = %d and size = %d\n", comand, size);
    if (comand == 2) {
        pthread_rwlock_rdlock(&(server_info->m_edit_users));
        for (int i = 1; i < server_info->size_connekt; i++)
            if (server_info->table_users[i].socket != -1) {
                printf("1 = %d\n", server_info->table_users[i].socket);
                int a = write(server_info->table_users[i].socket, "adadwawddwaadwawdawdawdawdadw", 10);
                printf("2 = %d %d\n", a, server_info->table_users[i].socket);
            }
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
}
