#include "client.h"
#include "libmx.h"

static int check(char *response, t_info *info) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "Error receive of msg = %d\n", response[9]);
        return 1;
    }
    return 0;
}

int mx_h_send_msg(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);

    if(check(response, info) == 1)
        return 0;
    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);

    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_handle_add_msg, data, 0);
    return 0;
}
