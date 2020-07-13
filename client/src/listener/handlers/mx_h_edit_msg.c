#include "client.h"

int mx_h_edit_msg(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_handle_edit_msg, data,
                              0);
    return 0;
}
