#include "client.h"

static void change_msg_data(t_msg *msg, char *data) {
    free(msg->msg_data);
    msg->msg_data = mx_strdup(data);
    gtk_label_set_text(GTK_LABEL(msg->msg_widget->label), msg->msg_data);
}

static void update_chat(t_chat_info*chat, t_msg *msg) {
    if (msg->msg_id < chat->last_id_msg 
        || chat->last_id_msg == 0)
    {
        chat->last_id_msg = msg->msg_id;
    }
}

static void insert_msg(t_info*info, char *response, t_chat_info *chat) {
    t_msg *msg = mx_get_msg_from_resp(response, info);
    // printf("msg->w = %d\n", msg->widget);
    int index = mx_add_msg_to_list(&chat->msgs, msg);
    mx_add_msg_to_box(chat->list_box, msg->msg_widget->widget, index);
    update_chat(chat, msg);
}

static int check(char *response, t_info *info) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "Error receive of msg = %d\n", response[9]);
        return 1;
    }
    return 0;
}

static gboolean handle_edit_msg(void* data) {
    t_info *info = (t_info*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    t_chat_info* chat = 0;
    t_msg *msg = 0;

    if(check(response, info) == 1)
        return 0;
    chat = mx_get_chat_info(info->list_of_chats, *(int*)&response[13]);
    if (chat == 0) { // if chat not exist
       mx_api_get_chat_info(*(int*)&response[13], info);
    }
    else { // if chat finded
        msg = mx_get_msg_by_id(chat->msgs, *(int*)&response[9]);
        if (msg != 0) {
            change_msg_data(msg, &response[46]);
            free(response);
            free(data);
            return 0;
        }
        insert_msg(info, response, chat);
    }
    free(response);
    free(data);
    return 0;
}

int mx_h_edit_msg(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, handle_edit_msg, data, 0);
    return 0;
}
