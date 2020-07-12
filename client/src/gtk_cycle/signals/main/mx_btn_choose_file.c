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

static bool set_file(t_file *file, t_info* info, char *filename) {
    struct stat st;

    if (stat(filename, &st) == -1) {
        free(file);
        return false;
    }
    file->chat_id = info->id_chat;
    file->unique_name = 0;
    file->fd = open(filename, O_RDONLY);
    if (file->fd == -1)
        printf("file open err = %s\n", strerror(errno));
    file->name = mx_get_not_dir(filename);
    file->pos = 0;
    file->size = st.st_size;
    return true;
}

void mx_btn_choose_file(GtkWidget *button, t_info *info) {
    char *filename = mx_show_file_dialog(info);
    t_file *file = malloc(sizeof(t_file));

    if (filename == 0)
        return;
    if (set_file(file, info, filename) == false)
        return;
    if (file->size == 0 || file->fd == -1) {
        free(file->name);
        free(file);
        return;
    }
    pthread_mutex_lock(&info->m_file_list);
    mx_push_back(&info->list_of_files, file);
    pthread_mutex_unlock(&info->m_file_list);
    mx_api_get_unique_name_of_file(info);
    free(filename);
}
