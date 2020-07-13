#include "server.h"
#include "defines.h"

void signal_stop(int sig) {
    system("leaks chat_server");
    exit(0);
}

static int check_and_create_socket(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./chat_server [port]\n");
        exit(1);
    }
    for(int i = 0; argv[1][i]; i++){
        if (argv[1][i] < '0' || argv[1][i] > '9' || i > 4) {
            fprintf(stderr, "error: namber port\n");
            exit(1);
        }
    }
    signal(SIGINT, signal_stop);
    return mx_create_sockl(atoi(argv[1]));
}

int main(int argc, char *argv[]) {
    int server_sockfd = check_and_create_socket(argc, argv);
    t_server *server_info = mx_create_server(server_sockfd);
    int rc = 0;

    while (1) {
        rc = poll(server_info->poll_set, server_info->size_connekt, -1);
        if (server_info->poll_set[0].revents & POLLIN) {
            rc += mx_accept_new_connect(server_info, MX_MAX_CONNECT);
            server_info->poll_set[0].revents = 0;
        }
        for (int i = 1; i < server_info->size_connekt && rc > 0; i++) {
            if ((server_info->poll_set[i].revents & POLLIN)
                && mx_check_not_work(&(server_info->table_users[i]))) {
                rc += mx_new_data_to_socket(server_info, i);
                server_info->poll_set[i].revents = 0;
            }
        }
        if (server_info->compress_array == true)
            mx_compress_array(server_info);
    }
}
