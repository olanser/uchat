#include "client.h"
#include "defines_client.h"

GtkWidget* mx_create_chat_widget(char *response) {
    GtkWidget* widget = gtk_button_new_with_label(&response[14]);

    gtk_widget_set_name(GTK_WIDGET (widget), "chat_names");
    return widget;
}

static GtkWidget* create_dialog_widget(char *response) {
    GtkWidget* widget = gtk_button_new_with_label("\0");

    gtk_widget_set_name(widget, "dialog_btn");
    return widget;
}

t_chat_info* mx_create_chat_info(char* response, t_info *info, 
                                 GtkWidget *chat_widget) {
    t_chat_info *chat_info = malloc(sizeof(t_chat_info));
    GtkBuilder* builder = gtk_builder_new_from_file(MX_TEMPLATE_SHITS);
    GtkWidget* chat_scroll_box = mx_build_get(builder, "chat_scroll_box");

    mx_set_adjustment_auto_down(builder);
    chat_info->list_box = mx_build_get(builder, "listbox_chat");
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

static void push_to_list(t_info *info, t_chat_info *chat_info, 
                         GtkWidget *chat_widget) {
    mx_push_back(&info->list_of_chats, chat_info);
    g_object_set_data(G_OBJECT(chat_widget), "chat_info", chat_info);
    gtk_list_box_insert(GTK_LIST_BOX(info->objs->chat_win->listbox_search),
                        chat_widget, -1);
    g_signal_connect(G_OBJECT(chat_widget), "clicked",
                     G_CALLBACK(mx_btn_change_chat), info);
    gtk_widget_show(chat_widget);
    mx_api_get_chat_msgs(chat_info->chat_id, 
                         chat_info->last_id_msg, 10, info);
}

gboolean mx_add_chat(void*data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];
    GtkWidget* chat_widget = 0;
    t_chat_info* chat_info = 0;

    if(mx_is_chat_exist(*(int*)&response[10], info->list_of_chats))
        return FALSE;
    if (response[9] == 50) { // chat
        chat_widget = mx_create_chat_widget(response);
        chat_info = mx_create_chat_info(response, info, chat_widget);
    }
    else { // dialog
        chat_widget = create_dialog_widget(response);
        chat_info = mx_create_dialog_info(response, info, chat_widget);
    }
    push_to_list(info, chat_info, chat_widget);
    free(response);
    free(data);
    return FALSE;
}