#include "client.h"

static gboolean get_file(void *data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];
    
    mx_handler_get_file(response, info);
    free(response);
    free(data);
    return false;
}

int mx_h_get_file(char *response, t_info *info) {

    void **data = malloc(sizeof(void*) * 2);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, get_file, data, 0);
    
    return 0;
}
