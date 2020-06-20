#include "header.h"
#include "defines.h"

static bool check_request(t_server_users *user) {
    char *response = 0;

    if (user->id_users) {
        if (user->buff[0] == 0 || user->buff[0] == 1 || user->buff[0] == 12) {
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_LOG_MANY);
        }
        else
            return true;
    }
    else {
        if (user->buff[0] == 0 || user->buff[0] == 1 || user->buff[0] == 12) {
            return true;
        }
        else {
            response = mx_create_response(user->buff[0],
                *(int*)&(user->buff[1]), MX_QS_ERR_RIGHT);
        }
    }
    pthread_mutex_lock(&(user->m_write_socket));
    mx_write_socket(user->socket, response);
    pthread_mutex_unlock(&(user->m_write_socket));
    free(response);
    return false;
}

void mx_work_thread(t_server *server_info, t_server_users *user) {
    char comand = user->buff[0];
    int size = *((int*)&(user->buff[5]));
    char *response;

    if (check_request(user)) {
        response = mx_do_request(server_info, user);
        if (response) {
        pthread_mutex_lock(&(user->m_write_socket));
        mx_write_socket(user->socket, response);
        pthread_mutex_unlock(&(user->m_write_socket));
        free(response);
        }
    }
    // // printf("Comand id = %d and size = %d\n", comand, size);
    // if (comand == 2) {
    //     pthread_rwlock_rdlock(&(server_info->m_edit_users));
    //     for (int i = 1; i < server_info->size_connekt; i++)
    //         if (server_info->table_users[i].socket != -1) {
    //             write(server_info->table_users[i].socket, "a", 1);
    //         }
    //     pthread_rwlock_unlock(&(server_info->m_edit_users));
    // }
    // int a = 1;
    // for (int i = 0; i < 200000000;i++)
    //     a *=i;
}
