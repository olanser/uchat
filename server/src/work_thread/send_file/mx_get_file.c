#include "server.h"
#include "defines.h"


static char *download_file(t_server_users *user) {
    char file_server_name[1024];
    unsigned int position = *((int*)&user->buff[17]);
    unsigned int count_bytes = *((int*)&user->buff[21]);
    char *response = malloc(21 + count_bytes);
    int file_fd = 0;
    
    sprintf(file_server_name, "%s/%d", MX_DIR_DOWNLOAD,
           *((int*)&user->buff[13]));
    file_fd = open(file_server_name, O_RDONLY);
    if (file_fd == -1) {
        printf("file_server_name  = %s: error: %s\n", file_server_name,
               strerror(errno));
        exit(0);
    }
    memset(response, 0, 21+count_bytes);
    response[0] = user->buff[0];
    *(int*)&response[1] = *((int*)&user->buff[1]);
    *(int*)&response[9] = *((int*)&user->buff[13]);
    *(unsigned int*)&response[17] = count_bytes;
    if (lseek(file_fd, position, SEEK_SET) == -1) {
        printf("ERROR LSEEK: %s\n", strerror(errno));
        exit(0);
    }
    count_bytes = read(file_fd, &response[21], count_bytes);
    *(int*)&response[5] = 21 + count_bytes;
    if (count_bytes == -1){
        printf("ERROR READ: %s\n", strerror(errno));
        exit(0);
    }
    close(file_fd);
    *(unsigned int*)&response[13] = position + count_bytes;
    return response;
}

char *mx_get_file(t_server *server_info, t_server_users *user) {
    char *res = NULL;

    if (mx_check_user_in_chat(*((int*)&user->buff[9]), user->id_users,
                        server_info) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_DONT_HAVE_CHAT_USER, MX_QS_ERR_RIGHT);
    res = download_file(user);
    return res;
}
