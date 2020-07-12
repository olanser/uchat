#include "client.h"
#include "defines_client.h"

static bool check(char *response) {
    if (*(int*)&response[5] < 12) {
        fprintf(stderr, "error check status = %d\n", response[10]);
        return false;
    }
    return true;
}

static void send_get_file(char *response, t_file *file, t_info *info) {
    int a[2] = {*(int*)&response[13], 1024};
    void *parameters[4] = {&file->msg_of_file->msg_id_chat,
        &file->msg_of_file->msg_id, &a[0], &a[1]};

    mx_api_get_file(parameters, info);
}

static bool file_downloaded(char *response, t_file *file, t_info *info) {
    if (*(int*)&response[13] >= (int)file->size) {
        GtkWidget *parent = gtk_widget_get_parent(
            file->msg_of_file->msg_widget->widget);

        gtk_widget_destroy(file->msg_of_file->msg_widget->widget);
        file->msg_of_file->msg_widget->widget = mx_get_widget_of_file(file);
        gtk_widget_show_all(file->msg_of_file->msg_widget->widget);
        gtk_container_add(GTK_CONTAINER(parent),
                          file->msg_of_file->msg_widget->widget);
        close(file->fd);
        return true;
    }
    return false;
}

int mx_handler_get_file(char *response, t_info *info) {
    t_file *file = 0;
    int size = *(int*)&response[5];
    char *buff = malloc(size);

    if (check(response) == false)
        return 0;
    pthread_mutex_lock(&info->m_file_recv_list);
    file = mx_get_file_by_msg_id(info->list_of_recv_files, 
        *(int*)&response[9]);
    pthread_mutex_unlock(&info->m_file_recv_list);
    if (file == 0) {
        return 0;
    }
    memcpy(buff, &response[21], size - 21);
    write(file->fd, buff, size - 21);
    if (file_downloaded(response, file, info))
        return 0;
    send_get_file(response, file, info);
    return 0;
}