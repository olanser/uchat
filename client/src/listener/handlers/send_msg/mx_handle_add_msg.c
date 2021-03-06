#include "client.h"
#include "defines_client.h"

bool is_msg_exist(t_chat_info *chat, int msg_id) {
    t_list *tmp = chat->msgs;

    while(tmp) {
        if (((t_msg*)tmp->data)->msg_id == msg_id)
            return true;
        tmp = tmp->next;
    }
    return false;
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
    int index = mx_add_msg_to_list(&chat->msgs, msg);
    gint width;
    gint height;

    gtk_widget_get_size_request(GTK_WIDGET (chat->list_box), &width, &height);
    mx_add_msg_to_box(chat->list_box, msg->msg_widget->widget, index);
    
    update_chat(chat, msg);
}

gboolean mx_handle_add_msg(void* data) {
    t_info *info = (t_info*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    t_chat_info* chat = 0;

    chat = mx_get_chat_info(info->list_of_chats, *(int*)&response[13]);
    if (chat == 0) { // if chat not exist
       mx_api_get_chat_info(*(int*)&response[13], info);
    }
    else { // if chat finded
        if (is_msg_exist(chat, *(int*)&response[9])) {
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
