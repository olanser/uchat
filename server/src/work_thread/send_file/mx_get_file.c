#include "server.h"
#include "defines.h"


static char *download_file(t_server_users *user) {
    char *file_server_name = mx_itoa(*((int*)&user->buff[13]));
    unsigned int position = *((int*)&user->buff[17]);
    unsigned int count_bytes = *((int*)&user->buff[21]);
    char *response = malloc(21 + count_bytes);
    int file_fd = open(file_server_name, O_RDONLY);
    free(file_server_name);

    printf("start\n");
    memset(response, 0, 21+count_bytes);
    response[0] = user->buff[0];
    *(int*)&response[1] = *((int*)&user->buff[1]);
    *(int*)&response[5] = 10;
    response[9] = 21 + count_bytes;
    *(int*)&response[9] = *((int*)&user->buff[13]);
    *(unsigned int*)&response[13] = position + count_bytes;
    *(unsigned int*)&response[17] = count_bytes;

    //lseek(file_fd, position, SEEK_SET);
    read(file_fd, &response[21], count_bytes);
    close(file_fd);
   
    printf("lollka in  - %d\n", response[0]);
    
    return response;

}
//{22}{id_of_query(4)}{size(4)}{chat_id(4)}{id_msg_of_file(4)}{position_in_file(4)}{count_bytes(4)}
//{22}{id_of_query(4)}{size(4)}{id_msg_of_file(4)}{position_in_file(4)}{count_bytes(4)}{data...}

char *mx_get_file(t_server *server_info, t_server_users *user) {
    char *res = NULL;
    user->id_users = 1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //check user
    //printf("lolli\n");
    printf("start1  \n");

    if (mx_check_user_in_chat(*((int*)&user->buff[9]), user->id_users,
                        server_info) == 0)
        return mx_create_respons_error_and_log(server_info, user,
            MX_DONT_HAVE_CHAT_USER, MX_QS_ERR_RIGHT);
    res = download_file(user);
    //printf("end\n");
    //printf("lollka - %d\n", res[0]);
    return res;

}
