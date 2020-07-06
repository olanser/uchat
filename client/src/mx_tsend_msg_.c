#include "client.h"

static void *func(void* arg) {
    int socket = (int)(((void**)arg)[0]);
    char *buff = (char*)(((void**)arg)[1]);
    int size = (int)(((void**)arg)[2]);
    t_info *info = (t_info*)(((void**)arg)[3]);

    mx_send_msg_(socket, buff, size, info);
    free(arg);
    free(buff);
    return (void*)0;
}

int mx_tsend_msg_(int socket, char *abuff, int size, t_info *info) {
    pthread_t thread;
    void **mas = malloc(sizeof(void*) * 4);

    mas[0] = (void*)(long long)socket;
    mas[1] = abuff;
    mas[2] = (void*)(long long)size;
    mas[3] = info;
    pthread_create(&thread, 0, func, mas);
    return 0;
}
