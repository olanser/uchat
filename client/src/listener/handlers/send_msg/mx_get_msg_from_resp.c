#include "client.h"
#include "libmx.h"

static char *get_last(char **mas) {
    int i = -1;

    while (mas[++i]);
    if ( i == 0)
        return 0;
    return mas[i - 1];
}


static int check_type(char *extension) {
    int file_type = 6;

    if (strcmp(extension, "png") == 0 || strcmp(extension, "jpg") == 0
        || strcmp(extension, "bmp") == 0) {
        file_type = 1;
    }
    if (strcmp(extension, "txt") == 0 || strcmp(extension, "doc") == 0
        || strcmp(extension, "docx") == 0) {
        file_type = 2;
    }
    return file_type;
}

static int get_file_type(char *file_name) {
    int file_type = 6;
    char **file_res = mx_strsplit(file_name, '.');
    char *extension = get_last(file_res);

    file_type = check_type(extension);
    if (strcmp(extension, "mp4") == 0 || strcmp(extension, "avi") == 0
        || strcmp(extension, "mov") == 0 || strcmp(extension, "wav") == 0) {
        file_type = 3;
    }
    if (strcmp(extension, "mp3") == 0 || strcmp(extension, "m4a") == 0)
        file_type = 4;
    if (strcmp(extension, "rar") == 0 || strcmp(extension, "zip") == 0)
        file_type = 5;
    mx_del_strarr(&file_res);
    return file_type;
}

void init_tmp(t_msg *msg) {
    msg->msg_data = 0;
    msg->msg_f_name_of_file = 0;
    msg->msg_f_size = 0;
    msg->msg_f_type = 0;
}

t_msg* mx_get_msg_from_resp(char *resp, t_info *info) {
    t_msg *msg = malloc(sizeof(t_msg));

    msg->msg_id = *(int*)&resp[9];
    msg->msg_id_chat = *(int*)&resp[13];
    msg->msg_id_user = *(int*)&resp[17];
    msg->msg_avatar = resp[41];
    msg->msg_type = *(int*)&resp[42];
    msg->msg_time = mx_strdup(&resp[21]);
    init_tmp(msg);
    if (msg->msg_type == 3) {
        msg->msg_f_name_of_file = mx_strdup(&resp[46]);
        msg->msg_f_type = get_file_type(msg->msg_f_name_of_file);
        msg->msg_f_size = *(int*)&resp[303];
    }
    else
        msg->msg_data = mx_strdup(&resp[46]);
    msg->msg_widget = mx_get_msg_widget(resp, info, msg);
    return msg;
}
