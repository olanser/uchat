#include "server.h"

static int callback(void *data, int column, char **name, char **tabledata) {
    char *respons = (char*)(((void**)data)[1]);
    t_server *server_info = (t_server *)(((void**)data)[0]);
    t_server_users *user = 0;
    int id_user = atoi(name[0]);
    char log[1024];

    for (int i = 1; i < server_info->size_connekt; i++) {
        user = &server_info->table_users[i];
        if (user->socket != -1 && user->id_users != 0) {
            if (id_user == user->id_users) {
                sprintf(log, "SEND msg id[0] = %d and id user = %d id msg = %d"
                        "\n", respons[0], user->id_users, *((int*)&respons[9]));
                mx_add_log(server_info, log);
                mx_write_socket(user, respons);
            }
        }
    }
    return 0;
}

void mx_send_response_user(t_server *server_info, char *response, char *sql) {
    void *send[2] = {server_info,response};
    printf("A // mx_send_response_user\n");
    pthread_rwlock_rdlock(&(server_info->m_edit_users));
    printf("B // mx_send_response_user\n");
    mx_do_query(sql, callback, send, server_info);
    pthread_rwlock_unlock(&(server_info->m_edit_users));
}
