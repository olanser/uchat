#include "client.h"
#include "defines_client.h"

/*
* add button to the left list box,
* create widget for new list of msgs
* add new node to list of chats
*/
static void add_new_chat(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 3);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_add_chat, data, 0);
}

static int check(char *response) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "get_chat_info_err = %d\n", response[9]);
        return 1;
    }
    return 0;
}

int mx_h_get_chat_info(char *response, t_info *info) {
    if (check(response) == 1)
        return 1;
    add_new_chat(response, info);
    return 0;
}
