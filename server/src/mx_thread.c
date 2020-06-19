#include "header.h"

void *mx_thread(void *data) {
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    int signo;

    while (1) {
        sigwait(&(newmask), &signo);
        printf("Test\n");
        sleep(5);
    }
    return 0;
}