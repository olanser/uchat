#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    *((char **)data) = mx_strdup(name[0]);
    return 0;
}

t_user* init_user(int socket) {
    t_user *new = malloc(sizeof(t_user));

    new->id = 0;
    new->username = 0;
    new->socket = socket;
    if (pthread_mutex_init(&new->m_fd, NULL) != 0) {
        fprintf(stderr, "Mutex create error\n");
        exit(1);
    }
    new->updates = malloc(sizeof(t_updates));
    sigemptyset(&(new->updates->newmask));
    sigaddset(&(new->updates->newmask), SIGUSR1);
    mx_do_query("select datetime('now');", callback, &(new->updates->time));
    new->updates->list_id = 0;
    new->updates->list_head = 0;
    return new;
}

void serve(int socket) {
    char *request;
    int len = 0;
    char *response = 0;
    t_user *user_info = init_user(socket);
    pthread_t preg2 = mx_create_pthread_updates(user_info);

    while (1) {
        len = mx_read_socket(socket, &request);
        len = mx_handle_input(request, &response, user_info);
        pthread_mutex_lock(&user_info->m_fd);
        mx_handle_out(socket, len, &response);
        pthread_mutex_unlock(&user_info->m_fd);
    }
}
