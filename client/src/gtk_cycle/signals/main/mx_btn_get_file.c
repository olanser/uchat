#include "client.h"
#include "defines_client.h"

void mx_btn_get_file(GtkButton *button, t_info *info) {
    t_msg* msg = g_object_get_data(G_OBJECT(button), "msg");
    t_file *file = malloc(sizeof(t_file));
    char name_of_file[1024];
    int a[2] = {0, 1024};
    void *parameters[4] = {&msg->msg_id_chat, &msg->msg_id, &a[0], &a[1]};

    memset(name_of_file, 0, 1024);
    strcat(name_of_file, MX_DIR_DOWNLOAD);
    mx_strcat(name_of_file, msg->msg_f_name_of_file);
    file->size = msg->msg_f_size;
    file->pos = 0;
    file->msg_of_file = msg;
    file->fd = open(name_of_file, O_CREAT | O_RDWR | O_TRUNC, S_IREAD | S_IWRITE);
    printf("BTN CLICKED\n");
    printf("file->size= %d\n", file->size);
    printf("name_of_file = %s\n", name_of_file);
    printf("msg_id_chat = %d\n", msg->msg_id_chat);
    printf("msg_id = %d\n", msg->msg_id);
    pthread_mutex_lock(&info->m_file_recv_list);
    mx_push_back(&info->list_of_recv_files, file);
    pthread_mutex_unlock(&info->m_file_recv_list);
    mx_api_get_file(parameters, info);
}
