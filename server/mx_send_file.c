#include "header.h"

static int save_file(void *request, t_user *user_info, t_file_message *file) {
    char path[63];
    int file_fd;
    int file_size = *(int *)(&request[10]);
    int last_bute = 0;
    int byte = 0;
    char buf[1024];
    int status = 0;

    sprintf(path, "%s/%s", "download", file->buf_name);
    file_fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);

    if (file_fd > 0) {
        if (file_size > 1024) {
            byte = 1024;
            last_bute = file_size%1024;
        }
        else
            byte = file_size;
        while (file_size > 0) {
                status = read(user_info->socket, buf, byte);
                write(file_fd, buf, byte);
                file_size -= 1024;
                if (file_size < 1024)
                    byte = last_bute;
                if (status == -1)
                    return 1;
        }


    }
        close(file_fd);
        return 0;
}

int mx_check_file(char *request, t_file_message *message) {
    int len = 0;

    message->id_query = &request[1];
    if (mx_check_number(&request[14], 11) == 0)
        return 0;
    message->id_chat = &request[14];
    message->true_name = &((char *)request)[25];
    message->size = *(int *)(&request[10]);
    message->buf_name[14] = 0;
    message->file_type = request[9];
    srand(time(NULL));
    for (int i = 0; i < 14; i++) {
        message->buf_name[i] = 49 + rand()%83;
    }
    return 1;
}

static void create_sql_request(t_file_message message, t_user *user_info, char *buf) {

    sprintf(buf, "INSERT INTO msg (msg_creator, msg_send_time, msg_file_type, msg_chat_id, msg_file_size, msg_status, msg_file_name) VALUES (%s, datetime('now'), %d, %s, %d, %s, '%s');", user_info->id, message.file_type, message.id_chat, message.size, "5", message.true_name);

}
static int callback_one(void *data, int columns, char **name, char **tabledata) {
    *(char **)data = strdup(name[0]);
    return 0;
}

int mx_send_file(void *request, char **response, t_user *user_info) {
    t_file_message message;
    char sql_request[500];
    char name[100];

    mx_create_response(request, response);
    if (mx_check_file(((char*)request), &message) == 0) {
        fprintf(MX_ERROR_THREAD, "not messege\n");
        (*response)[9] = (char)100;
        return 10;
    }
    if (mx_check_user_in_char(message.id_chat, user_info->id) == 0) {
        fprintf(MX_ERROR_THREAD, "permission\n");
        (*response)[9] = (char)103;
        return 10;
    }
    create_sql_request(message, user_info, sql_request);
    if (save_file(request, user_info, &message) == 0) {
        if (mx_do_query(sql_request,0,0) == 0) {
            (*response)[9] = (char)200;
            sprintf(sql_request, "SELECT msg_id from msg where msg_creator = '%s' ORDER by msg_id DESC LIMIT 1;", user_info->id);
            mx_do_query(sql_request, callback_one, &(message.id_message));
            sprintf(sql_request, "download/%s", message.buf_name);
            sprintf(name, "download/%s", message.id_message);
            rename(sql_request, name);
            mx_create_signal_new_message(message.id_chat);
            return 10;
        }
    
    }

    return 10;
}
