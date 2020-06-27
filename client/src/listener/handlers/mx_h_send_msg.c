#include "client.h"
#include "libmx.h"

GtkWidget* get_list_box(t_list* list, char *id) {
    t_list* tmp = list;

    while (tmp) {
        if (mx_strcmp(((t_chat_info*)tmp->data)->chat_id, id) == 0)
            return ((t_chat_info*)tmp->data)->list_box;
        tmp = tmp->next;
    }
    return 0;
}

void mx_add_msg_to_box(GtkWidget*listbox, char *response) {
    GtkWidget* label = gtk_label_new(&response[63]);
    gtk_list_box_insert(GTK_LIST_BOX(listbox), label, -1);
    gtk_widget_show(label);
}

int mx_h_send_msg(char *response, t_info *info) {
    printf("RECEIVE\n");
    // printf("id msg = %s\n", &response[9]);
    // printf("id chat = %s\n", &response[20]);
    // printf("id user = %s\n", &response[31]);
    // printf("time = %s\n", &response[42]);
    // printf("msg = %s\n", &response[63]);
    GtkWidget* listbox = get_list_box(info->list_of_chats, &response[20]);

    if (listbox == 0) {
       mx_api_get_chat_info(&response[20], info);
    }
    else {
        mx_add_msg_to_box(listbox, response);
    }
    return 0;
}
