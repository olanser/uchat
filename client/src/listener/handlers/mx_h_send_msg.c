#include "client.h"
#include "libmx.h"

/* find listbox of chat */
GtkWidget* get_list_box(t_list* list, int id) {
    t_list* tmp = list;

    while (tmp) {
        if (((t_chat_info*)tmp->data)->chat_id == id)
            return ((t_chat_info*)tmp->data)->list_box;
        tmp = tmp->next;
    }
    return 0;
}

static gboolean foo(void* data) {
    GtkWidget* listbox = (GtkWidget*)((void**)data)[0];
    char* response = (char*)((void**)data)[1];
    GtkWidget* label = gtk_label_new(&response[42]);

    gtk_list_box_insert(GTK_LIST_BOX(listbox), label, -1);
    gtk_widget_show(label);
    
    free(response);
    free(data);
    return FALSE;
}

void mx_add_msg_to_box(GtkWidget*listbox, char *response) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = listbox;
    data[1] = malloc(*(int*)&response[5]);
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

int mx_h_send_msg(char *response, t_info *info) {
    printf("RECEIVE\n");
    // printf("id msg = %s\n", &response[9]);
    // printf("id chat = %s\n", &response[20]);
    // printf("id user = %s\n", &response[31]);
    // printf("time = %s\n", &response[42]);
    // printf("msg = %s\n", &response[63]);
    GtkWidget* listbox = 0;

    if(check(response, info) == 1)
        return 1;
    listbox = get_list_box(info->list_of_chats, *(int*)&response[13]);
    if (listbox == 0) { // if not exist
       mx_api_get_chat_info(*(int*)&response[13], info);
    }
    else { // if listbox finded

        mx_add_msg_to_box(listbox, response);
    }
    printf("END RECEIVE\n");
    return 0;
}
