#include "client.h"

static bool check(char *response) {
    if (response == 0 || *(int*)&response[5] < 10) {
        return false;
    }
    return true;
}

void mx_delete_msg(t_msg *msg) {
    gtk_widget_destroy(msg->msg_widget->widget);
    free(msg->msg_widget);
    free(msg->msg_time);
    free(msg->msg_data);
    free(msg);
}

static gboolean handle_delete_msg(void* data) {
    t_info *info = (t_info*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    t_chat_info* chat = 0;
    t_msg *msg = 0;

    if (check(response) == false)
        return 1;
    msg = mx_find_msg(info->list_of_chats, *(int*)&response[9], *(int*)&response[13]);
    if (msg == 0)
        return 0;
    mx_delete_msg(msg);
    free(response);
    free(data);
    return 0;
}

int mx_h_delete_msg(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, handle_delete_msg, data, 0);
    return 0;
}
