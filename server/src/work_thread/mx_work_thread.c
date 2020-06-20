#include "header.h"


// static bool check_request(t_server_users *user) {
//     if (user->id_users) {

//     }
//     else {

//     }
// }

void mx_work_thread(t_server *server_info, t_server_users *user) {
    char comand = user->buff[0];
    int size = *((int*)&(user->buff[5]));

    // if (check_request(user))
    // printf("Comand id = %d and size = %d\n", comand, size);
    if (comand == 2) {
        pthread_rwlock_rdlock(&(server_info->m_edit_users));
        for (int i = 1; i < server_info->size_connekt; i++)
            if (server_info->table_users[i].socket != -1) {
                write(server_info->table_users[i].socket, "a", 1);
            }
        pthread_rwlock_unlock(&(server_info->m_edit_users));
    }
    int a = 1;
    for (int i = 0; i < 200000000;i++)
        a *=i;
}
