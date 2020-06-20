#include "header.h"
#include "defines.h"

void signal_stop(int sig) {
    system("leaks server");
    exit(0);
}

int main() {
    int port = MX_PORT_test;
    int server_sockfd = mx_create_sockl(port);
    int max_connect = MX_MAX_CONNECT - 5;
    int count_thread = MX_THREAD;
    t_server *server_info = mx_create_server(max_connect, server_sockfd,
                                             count_thread);
    int rc = 0;

    signal(SIGINT, signal_stop);
    while (1) {
        rc = poll(server_info->poll_set, server_info->size_connekt, -1);
        if (server_info->poll_set[0].revents & POLLIN) {
            rc += mx_accept_new_connect(server_info, max_connect);
            server_info->poll_set[0].revents = 0;
        }
        for (int i = 1; i < server_info->size_connekt && rc > 0; i++) {
            if (server_info->poll_set[i].revents & POLLIN && mx_check_not_work(
                server_info->table_users[i])) {
                rc += mx_new_data_to_socket(server_info, i);
                server_info->poll_set[i].revents = 0;
            }
        }
        if (server_info->compress_array == true)
            mx_compress_array(server_info);
        for (int i = 1; i < server_info->size_connekt; i++)
        printf("%d ", server_info->poll_set[i].fd);
        printf("\n");
        //usleep(1000);
    }
}
