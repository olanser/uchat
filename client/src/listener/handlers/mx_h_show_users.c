#include "client.h"
#include "libmx.h"

void show_users(char *response, t_info *info) {
    int i = 14;
    int j = 0;
    
    for (j = 0; j < 10; j++) {
        gtk_widget_hide(info->objs->chat_win->user_widgets[j]);  
    }
    j = 0;
    while (i < *(int*)&response[5]) {
        printf("nick = %s\n", &response[i]);
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(info->objs->chat_win->user_widgets[j]));
        gtk_label_set_text(GTK_LABEL(label) ,&response[i]);
        gtk_widget_show(info->objs->chat_win->user_widgets[j]);
        t_user_info* user_info = g_object_get_data(G_OBJECT(info->objs->chat_win->user_widgets[j]), "user_info");
        user_info->id = *(int*)&response[i - 4];
        i += 105;
        j++;
    }
}

static gboolean thread_show(void*data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];
    show_users(response, info);
    free(response);
    free(data);
    return FALSE;
}

int mx_h_show_users(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);
    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, thread_show, data, 0);
    
    return 0;
}
