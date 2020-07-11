#include "server.h"
#include "defines.h"

static void save_file(t_server_users *user, char *unique_name, char *request) {
    char path[63];
    int file_fd;
    char *buf = &request[18];

    sprintf(path, "%s/%s", "download", unique_name);
    file_fd = open(path, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
    write(file_fd, buf, *((int *)&request[5]) - 18);
    close(file_fd);
}



static char *get_unique_name(char *request, t_server_users *user) {
    int user_req_id = *((int *)&request[9]);

    if (user->id_users != user_req_id)
        return NULL;
    else
    {
        char *first_part = mx_itoa(user_req_id);
        char *second_part = mx_itoa(*((int *)&request[13]));
        char *unique_name = mx_strjoin3(first_part, second_part);

        return unique_name;
    }
}

char *mx_send_file(t_server *server_info, t_server_users *user) {
    t_file_message message;
    char *uniq_name = NULL;
    char *request = user->buff;

    user->id_users = 1;
    uniq_name = get_unique_name(request, user);
    if (uniq_name != NULL) {
        save_file(user, uniq_name, request);
        free(uniq_name);
    }
    else
        printf("ERROR file\n");
    return 0;
}
