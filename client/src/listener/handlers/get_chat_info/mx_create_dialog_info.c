#include "client.h"
#include "defines_client.h"

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

t_chat_info* mx_create_dialog_info(char* response, t_info *info, 
                                    GtkWidget *chat_widget) {
    t_chat_info *chat_info = malloc(sizeof(t_chat_info));
    GtkBuilder* builder = gtk_builder_new_from_file(MX_TEMPLATE_SHITS);
    GtkWidget* chat_scroll_box = mx_build_get(builder, "chat_scroll_box");

    mx_set_adjustment_auto_down(builder);
    chat_info->list_box = mx_build_get(builder, "listbox_chat");
    chat_info->node_index = gtk_notebook_append_page(
            GTK_NOTEBOOK(info->objs->chat_win->notebook), chat_scroll_box, 0);
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
