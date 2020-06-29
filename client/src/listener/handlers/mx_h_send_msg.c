#include "client.h"
#include "libmx.h"

/* find listbox of chat */
t_chat_info* get_chat_info(t_list* list, int id_chat) {
    t_list* tmp = list;

    while (tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == id_chat)
            return ((t_chat_info*)tmp->data);
        tmp = tmp->next;
    }
    return 0;
}

static gboolean add_msg(void* data) {
    GtkWidget* listbox = (GtkWidget*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    int index = (int)(long long)((void**)data)[2];
    GtkWidget* label = gtk_label_new(&response[46]);
    gtk_list_box_insert(GTK_LIST_BOX(listbox), label, index);
    gtk_widget_show(label);
    
    free(response);
    free(data);
    return FALSE;
}

GtkWidget* get_image(int number) {
    GtkWidget *img = 0;
    char *name = mx_get_path_to_sticker(number);

    img = gtk_image_new_from_file(name);
    free(name);
    return img;
}

static gboolean add_sticker(void* data) {
    GtkWidget* listbox = (GtkWidget*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    int index = (int)(long long)((void**)data)[2];
    GtkWidget* image = get_image(*(int*)&response[46]);

    gtk_list_box_insert(GTK_LIST_BOX(listbox), image, index);
    gtk_widget_show(image);
    
    free(response);
    free(data);
    return FALSE;
}

void mx_add_msg_to_box(GtkWidget*listbox, char *response, int index) {
    void **data = malloc(sizeof(void*) * 3);
    data[0] = listbox;
    data[1] = malloc(*(int*)&response[5]);
    data[2] = (void*)(long long)index;
    memcpy(data[1], response, *(int*)&response[5]);
    if (*(int*)&response[42] == 1)
        gdk_threads_add_idle(add_msg, data);
    else
        gdk_threads_add_idle(add_sticker, data);
}

int check(char *response, t_info *info) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "Error receive of msg = %d\n", response[9]);
        return 1;
    }
    return 0;
}

t_msg* mx_get_msg_from_resp(char *resp) {
    t_msg *msg = malloc(sizeof(t_msg));

    msg->msg_id = *(int*)&resp[9];
    msg->msg_id_chat = *(int*)&resp[13];
    msg->msg_id_user = *(int*)&resp[17];
    msg->msg_avatar = *(int*)&resp[41];
    msg->msg_type = *(int*)&resp[42];
    return msg;
}

/* add to list and return index*/
int mx_add_msg_to_list(t_list **list_, t_msg *msg) {
    t_list *list = *list_;
    t_list *new = 0;
    t_list *tmp = list;
    int i = 1;

    //if enmty or first less than new
    if (list == 0 || (((t_msg*)list->data)->msg_id > msg->msg_id)) {
        printf("AA\n");
        mx_push_front(list_, msg);
        return 0;
    }
    while (tmp->next && ((t_msg*)tmp->next->data)->msg_id < msg->msg_id) {
        i++;
        tmp = tmp->next;
    }
    new = mx_create_node(msg);
    new->next = tmp->next;
    tmp->next = new;
    return i;
}

bool is_msg_exist_free(t_chat_info *chat, t_msg *msg) {
    t_list *tmp = chat->msgs;

    while(tmp) {
        if (((t_msg*)tmp->data)->msg_id == msg->msg_id) {
            free(msg);
            return true;
        }
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

int mx_h_send_msg(char *response, t_info *info) {
    t_chat_info* chat = 0;
    t_msg *msg = 0;
    int index = 0;

    if(check(response, info) == 1)
        return 1;
    chat = get_chat_info(info->list_of_chats, *(int*)&response[13]);
    if (chat == 0) { // if not exist
       mx_api_get_chat_info(*(int*)&response[13], info);
    }
    else { // if listbox finded
        
        msg = mx_get_msg_from_resp(response);
        if (is_msg_exist_free(chat, msg))
            return 1;
        index = mx_add_msg_to_list(&chat->msgs, msg);
        mx_add_msg_to_box(chat->list_box, response, index);
        update_chat(chat, msg);
    }
    return 0;
}
