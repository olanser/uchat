#include "server.h"
#include "defines.h"


static char *create_response(t_server_users *user) {
    unsigned int count_bytes = *((int*)&user->buff[21]);
    char *response = malloc(21 + count_bytes);

    memset(response, 0, 21 + count_bytes);
    response[0] = user->buff[0];
    *(int*)&response[1] = *((int*)&user->buff[1]);
    *(int*)&response[9] = *((int*)&user->buff[13]);
    *(unsigned int*)&response[17] = count_bytes;
    return response;
}

static char *open_file_and_set_start_pos(t_server *server_info,
                                         t_server_users *user, int *fd) {
    int file_fd;
    char file_server_name[512];
    unsigned int position = *((int*)&user->buff[17]);

    sprintf(file_server_name, "%s/%d", MX_DIR_DOWNLOAD,
           *((int*)&user->buff[13]));
    file_fd = open(file_server_name, O_RDONLY);
    if (file_fd == -1)
        return mx_create_respons_error_and_log(server_info, user,
            "ERROR OPEN FILE!!!", MX_QS_ERR_SERV);
    if (lseek(file_fd, position, SEEK_SET) == -1) {
        close(file_fd);
        return mx_create_respons_error_and_log(server_info, user,
            "ERROR LSEEK FILE!!!", MX_QS_ERR_SERV);
    }
    *fd = file_fd;
    return 0;
}


static char *download_file(t_server *server_info, t_server_users *user) {
    char file_server_name[1024];
    unsigned int position = *((int*)&user->buff[17]);
    unsigned int count_bytes = *((int*)&user->buff[21]);
    int file_fd = 0;
    char *response = open_file_and_set_start_pos(server_info, user, &file_fd);

    if (response)
        return response;
    response = create_response(user);
    count_bytes = read(file_fd, &response[21], count_bytes);
    close(file_fd);
    if (count_bytes == -1) {
        free(response);
        return mx_create_respons_error_and_log(server_info, user,
            "ERROR READ FILE!!!", MX_QS_ERR_SERV);
    }
    *(int*)&response[5] = 21 + count_bytes;
    *(unsigned int*)&response[13] = position + count_bytes;
    return response;
}

char *mx_get_file(t_server *server_info, t_server_users *user) {
    char *res = NULL;

    if (mx_check_user_in_chat(*((int*)&user->buff[9]), user->id_users,
                        server_info) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_DONT_HAVE_CHAT_USER, MX_QS_ERR_RIGHT);
    res = download_file(server_info, user);
    return res;
}
