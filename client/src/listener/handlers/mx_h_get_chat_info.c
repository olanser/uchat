#include "client.h"
#include "defines.h"

static GtkWidget* mx_create_chat_widget(char *response) {
    GtkWidget* widget = gtk_button_new_with_label(&response[14]);
    return widget;
}

static int get_user_id(char *name, int main_user_id) {
    int id = 0;
    char *main_id = 0;
    char **strs = 0;

    main_id = mx_itoa(main_user_id);
    strs = mx_strsplit(name, '_');
    if (mx_strcmp(strs[0], main_id) == 0)
        id = atoi(strs[1]);
    else 
        id = atoi(strs[0]);
    mx_del_strarr(&strs);
    free(main_id);
    return id;
}

static GtkWidget* mx_create_dialog_widget(char *response) {
    GtkWidget* widget = gtk_button_new_with_label("\0");
    return widget;
}

static t_chat_info* get_chat_info(char* response, t_info *info, GtkWidget *chat_widget) {
    t_chat_info *chat_info = malloc(sizeof(t_chat_info));
    GtkBuilder* builder = gtk_builder_new_from_file(MX_TEMPLATE_SHITS);
    // notebool widget
    GtkWidget* chat_scroll_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_scroll_box"));

    // inside scroll box
    chat_info->list_box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_chat"));
    chat_info->node_index = gtk_notebook_append_page(
            GTK_NOTEBOOK(info->objs->chat_win->notebook), // notebook
            chat_scroll_box, // widget inside notebook
            0); // label
    chat_info->chat_id = *(int*)&response[10];
    chat_info->msgs = 0;
    chat_info->last_id_msg = 0;
    chat_info->type_of_chat = response[9];
    chat_info->name = mx_strdup(&response[14]);
    chat_info->id_user = 0;
    chat_info->chat_widget = chat_widget;
    return chat_info;
}

static t_chat_info* get_dialog_info(char* response, t_info *info, GtkWidget *chat_widget) {
    t_chat_info *chat_info = malloc(sizeof(t_chat_info));
    GtkBuilder* builder = gtk_builder_new_from_file(MX_TEMPLATE_SHITS);
    // notebool widget
    GtkWidget* chat_scroll_box = GTK_WIDGET(gtk_builder_get_object(builder, "chat_scroll_box"));

    // inside scroll box
    chat_info->list_box = GTK_WIDGET(gtk_builder_get_object(builder, "listbox_chat"));
    chat_info->node_index = gtk_notebook_append_page(
            GTK_NOTEBOOK(info->objs->chat_win->notebook), // notebook
            chat_scroll_box, // widget inside notebook
            0); // label
    chat_info->chat_id = *(int*)&response[10];
    chat_info->msgs = 0;
    chat_info->last_id_msg = 0;
    chat_info->type_of_chat = response[9];
    chat_info->id_user = get_user_id(&response[14], info->user_info->id);
    mx_api_get_user_info(chat_info->id_user, info);
    chat_info->name = 0;
    chat_info->chat_widget = chat_widget;
    return chat_info;
}

static gboolean add_chat(void*data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];
    GtkWidget* chat_widget = 0;
    t_chat_info* chat_info = 0;

    if(mx_is_chat_exist(*(int*)&response[10], info->list_of_chats))
        return FALSE;
    if (response[9] == 50) {
        chat_widget = mx_create_chat_widget(response);
        chat_info = get_chat_info(response, info, chat_widget);
    }
    else {
        chat_widget = mx_create_dialog_widget(response);
        chat_info = get_dialog_info(response, info, chat_widget);
    }
    mx_push_back(&info->list_of_chats, chat_info);
    // add to chat widget chat data
    g_object_set_data(G_OBJECT(chat_widget), "chat_info", chat_info);
    // insert chat
    gtk_list_box_insert(GTK_LIST_BOX(info->objs->chat_win->listbox_search), chat_widget, -1);
    g_signal_connect(G_OBJECT(chat_widget), "clicked", G_CALLBACK(mx_btn_change_chat), info);
    gtk_widget_show(chat_widget);
    free(response);
    free(data);
    return FALSE;
}

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
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, add_chat, data, 0);
}

static int check(char *response) {
    if (*(int*)&response[5] < 11) {
        fprintf(stderr, "get_chat_info_err = %d\n", response[9]);
        return 1;
    }
    return 0;
}

int mx_h_get_chat_info(char *response, t_info *info) {
    if(check(response) == 1)
        return 1;
    add_new_chat(response, info);
    return 0;
}
