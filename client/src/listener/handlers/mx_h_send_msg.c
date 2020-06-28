#include "client.h"
#include "libmx.h"

/* find listbox of chat */
t_chat_info* get_chat_info(t_list* list, int id) {
    t_list* tmp = list;

    while (tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == id)
            return ((t_chat_info*)tmp->data);
        tmp = tmp->next;
    }
    return 0;
}

static gboolean foo(void* data) {
    GtkWidget* listbox = (GtkWidget*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    int index = (int)(long long)((void**)data)[2];
    GtkWidget* label = gtk_label_new(&response[42]);
    gtk_list_box_insert(GTK_LIST_BOX(listbox), label, index);
    gtk_widget_show(label);
    
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
    gdk_threads_add_idle(foo, data);
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
    msg->msg_avatar = resp[41];
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

int mx_h_send_msg(char *response, t_info *info) {
    printf("RECEIVE\n");
    // printf("id msg = %s\n", &response[9]);
    // printf("id chat = %s\n", &response[20]);
    // printf("id user = %s\n", &response[31]);
    // printf("time = %s\n", &response[42]);
    // printf("msg = %s\n", &response[63]);
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
        index = mx_add_msg_to_list(&chat->msgs, msg);
        printf("index = %d\n", index);
        mx_add_msg_to_box(chat->list_box, response, index);
    }
    return 0;
}
