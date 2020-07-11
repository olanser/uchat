#include "client.h"

static void change_msg_data(t_msg *msg, char *data) {
    free(msg->msg_data);
    msg->msg_data = mx_strdup(data);
    gtk_label_set_text(GTK_LABEL(msg->msg_widget->label), msg->msg_data);
}

static void insert_msg(t_info*info, char *response, t_chat_info *chat) {
    t_msg *msg = mx_get_msg_from_resp(response, info);
    int index = mx_add_msg_to_list(&chat->msgs, msg);

    mx_add_msg_to_box(chat->list_box, msg->msg_widget->widget, index);
    if (msg->msg_id < chat->last_id_msg 
        || chat->last_id_msg == 0) {
        chat->last_id_msg = msg->msg_id;
    }
}

static int check(char *response, t_info *info) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "Error receive of msg = %d\n", response[9]);
        return 1;
    }
    return 0;
}

static bool chat_filded(t_info *info, t_chat_info *chat, char *response) {
    t_msg *msg = 0;

    msg = mx_get_msg_by_id(chat->msgs, *(int*)&response[9]);
    if (msg != 0) {
        change_msg_data(msg, &response[46]);
        free(response);
        return false;
    }
    insert_msg(info, response, chat);
    return true;
}

gboolean mx_handle_edit_msg(void* data) {
    t_info *info = (t_info*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    t_chat_info* chat = 0;

    if(check(response, info) == 1)
        return 0;
    chat = mx_get_chat_info(info->list_of_chats, *(int*)&response[13]);
    if (chat == 0) { // if chat not exist
       mx_api_get_chat_info(*(int*)&response[13], info);
    }
    else { // if chat finded
        if (!chat_filded(info, chat, response)) {
            free(data);
            return 0;
        }
    }
    free(response);
    free(data);
    return 0;
}
