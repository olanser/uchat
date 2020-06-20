#include "mxinet.h"

static void *func(void* arg) {
    int socket = *(int*)(((void**)arg)[0]);
    char *buff = (char*)(((void**)arg)[1]);
    int size = *(int*)(((void**)arg)[2]);

    mx_send_msg(socket, buff, size);
    free(arg);
    return (void*)0;
}

int mx_tsend_msg(int socket, char *buff, int size) {
    pthread_t thread;
    void **mas = malloc(sizeof(void*) * 3);
    mas[0] = &socket;
    mas[1] = buff;
    mas[2] = &size;
    pthread_create(&thread, 0, func, mas);
    return 0;
}
