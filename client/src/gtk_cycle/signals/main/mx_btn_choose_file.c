#include "client.h"

static char *mx_get_not_dir(char *full_name) {
    int index = mx_strlen(full_name) - 1;
    char str[256];
    int i = 0;

    memset(str, 0, 256);

    if (full_name[index] == '/') {
        index--;
    }
    while (full_name[index] != '/' && index >= 0) {
        str[i++] = full_name[index--];
    }
    mx_str_reverse(str);
    return mx_strdup(str);
}

void mx_btn_choose_file(GtkWidget *button, t_info *info) {
    char *filename = mx_show_file_dialog(info);
    t_file *file = malloc(sizeof(t_file));
    struct stat st;

    if (filename == 0)
        return;
    stat(filename, &st);
    file->chat_id = info->id_chat;
    file->unique_name = 0;
    file->fd = open(filename, O_RDONLY);
    file->name = mx_get_not_dir(filename);
    file->pos = 0;
    file->size = st.st_size;
    pthread_mutex_lock(&info->m_file_list);
    mx_push_back(&info->list_of_files, file);
    pthread_mutex_unlock(&info->m_file_list);
    mx_api_get_unique_name_of_file(info);
    free(filename);
}
