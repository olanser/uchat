#include "client.h"
#include "defines.h"

static bool is_exist(char *id, t_list* list_of_chats) {
    t_list* tmp = list_of_chats;

    while(tmp) {
        if (mx_strcmp(((t_chat_info*)tmp->data)->chat_id, id) == 0) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

static void fill_structure(t_chat_info* chat_info, char* response, t_info *info) {
    GtkBuilder* builder = gtk_builder_new_from_file(MX_TEMPLATE_SHITS);
    GtkWidget* chat_scroll_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_scroll_box"));

    chat_info->list_box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_chat"));
    chat_info->node_index = gtk_notebook_append_page(
        GTK_NOTEBOOK(info->objs->chat_win->notebook),
        chat_scroll_box,
        0);
    chat_info->chat_id = mx_strdup(&response[10]);

}

/* 
* add button to the left list box,
* create widget for new list of msgs
* add new node to list of chats
*/
static void add_new_chat(char *response, t_info *info) {
    GtkWidget* listbox_search = info->objs->chat_win->listbox_search;
    GtkWidget* chat_widget = gtk_button_new_with_label(&response[21]);
    t_chat_info* chat_info = malloc(sizeof(t_chat_info));

    pthread_mutex_lock(&info->m_editing_gtk);
    fill_structure(chat_info, response, info);
    mx_push_back(&info->list_of_chats, chat_info);
    g_object_set_data(G_OBJECT(chat_widget), "chat_info", chat_info);
    gtk_list_box_insert(GTK_LIST_BOX(listbox_search), chat_widget, -1);
    g_signal_connect(G_OBJECT(chat_widget), "clicked", G_CALLBACK(mx_btn_change_chat), info);
    gtk_widget_show(chat_widget);
    pthread_mutex_unlock(&info->m_editing_gtk);
}

int mx_h_get_chat_info(char *response, t_info *info) {

    if(is_exist(&response[10], info->list_of_chats))
        return 1;
    add_new_chat(response, info);

    // GtkWidget* chat_label = gtk_label_new(&response[21]);
    // t_chat_info* chat_info = malloc(sizeof(t_chat_info));

    // chat_info->chat_id = mx_strdup(&response[21]);
    // mx_push_back(&info->list_of_chats, chat_info);
    // g_object_set_data(G_OBJECT(chat_label), "chat_info", chat_info);
    return 0;
}
