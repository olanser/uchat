#include "server.h"
#include "defines.h"

static void save_file(t_server_users *user, char *unique_name,
                      char *request) {
    char path[63];
    int file_fd;
    char *buf = &request[18];

    sprintf(path, "%s/%s", MX_DIR_DOWNLOAD, unique_name);
    file_fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
    if (file_fd == -1) {
        fprintf(stderr, "file err // save file = %s\n", strerror(errno));
        return;
    }
    write(file_fd, buf, *((int *)&request[5]) - 18);
    close(file_fd);
}



static char *get_unique_name(char *request, t_server_users *user) {
    int user_req_id = *((int *)&request[9]);
    char *first_part = 0;
    char *second_part = 0;
    char *unique_name = 0;

    if (user->id_users != user_req_id)
        return NULL;
    else {
        first_part = mx_itoa(user_req_id);
        second_part = mx_itoa(*((int *)&request[13]));
        unique_name = mx_strjoin3(first_part, second_part);
        return unique_name;
    }
}

char *mx_send_file(t_server *server_info, t_server_users *user) {
    t_file_message message;
    char *uniq_name = NULL;
    char *request = user->buff;

    uniq_name = get_unique_name(request, user);
    if (uniq_name != NULL) {
        save_file(user, uniq_name, request);
        free(uniq_name);
    }
    else
        printf("ERROR file\n");
    return 0;
}
