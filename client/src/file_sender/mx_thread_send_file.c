#include "client.h"
#include "mxinet.h"
#include "defines_client.h"

static sigset_t set_mask(void) {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    return newmask;
}

void *mx_thread_send_file(void *data) {
    t_info *info = (t_info*)data;
    mx_init_signals();
    sigset_t newmask = set_mask();
    int signo;

    while (1) {
        sigwait(&(newmask), &signo);
        mx_write_file(info);
    }
    return (void*)0;
}
