#include "mxinet.h"

static void *func(void* arg) {
    int socket = (int)(((void**)arg)[0]);
    char *buff = (char*)(((void**)arg)[1]);
    int size = (int)(((void**)arg)[2]);

    mx_send_msg(socket, buff, size);
    free(arg);
    free(buff);
    return (void*)0;
}

int mx_tsend_msg(int socket, char *abuff, int size) {
    pthread_t thread;
    void **mas = malloc(sizeof(void*) * 3);

    mas[0] = (void*)(long long)socket;
    mas[1] = abuff;
    mas[2] = (void*)(long long)size;
    pthread_create(&thread, 0, func, mas);
    return 0;
}
