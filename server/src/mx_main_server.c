#include "header.h"
#include "mxinet.h"
#include "defines.h"

int main() {
    int port = MX_PORT_test;
    int server_sockfd = mx_create_sockl(port);
    int max_connect = MX_MAX_CONNECT - 5;
    int count_thread = MX_THREAD;
    t_server *server_info = mx_create_server(max_connect, server_sockfd, count_thread);
    int rc = 0;

    while (1) {
        // printf("1\n");
        rc = poll(server_info->poll_set, server_info->size_connekt, 1);
        mx_check_return_work(server_info);
        if (server_info->poll_set[0].revents & POLLIN) {
            rc += mx_accept_new_connect(server_info, max_connect);
            server_info->poll_set[0].revents = 0;
        }
        for (int i = 1; i < server_info->size_connekt && rc > 0; i++) {
            if (server_info->poll_set[i].revents & POLLIN) {
                rc += mx_new_data_to_socket(server_info, i);
                server_info->poll_set[i].revents = 0;
            }
        }
    }
}
/*
        // printf("1\n");
        if (server_info->poll_set[0].revents & POLLIN) {
            server_info->table_users[server_info->size_connekt].socket = accept(server_sockfd, 0, 0);
            server_info->poll_set[server_info->size_connekt].fd = server_info->table_users[server_info->size_connekt].socket;
            server_info->size_connekt++;
            printf("server connekt = %d\n", server_info->poll_set[server_info->size_connekt -  1].fd );
        }
        for (int i = 1; i < server_info->size_connekt && rc > 0; i++) {
            if (server_info->poll_set[i].revents & POLLIN) {
                check = read(server_info->poll_set[i].fd, buff, 1024);
                if (check <= 0) {
                    
                }
                printf("write socket  =%d read = %d\n", server_info->poll_set[i].fd, check);
            }
            else if (server_info->poll_set[i].revents & POLLHUP) {
                printf("exit users = %d\n", server_info->poll_set[i].fd);
                exit(1);
            }
            else if (server_info->poll_set[i].revents & POLLERR) {
                printf("exit users = %d\n", server_info->poll_set[i].fd);
                exit(1);
            }
        }
    }
}
*/
/*
    // struct pollfd poll_set[POLL_SIZE];
    // int numfds = 0;
    // int max_fd = 0;
    // bool end_server = 0;
    // bool close_conn = 0;
    // bool compress_array = 0;
    // pthread_t preg;
    // sigset_t newmask;

    struct sockaddr client_address;
    int client_len;
    int client_sockfd;
    int nread;
    int rc = 0;
    char buffer[1024];
    int len;
    // int server_sockfd = 0;






    // sigemptyset(&newmask);
    // sigaddset(&newmask, SIGUSR1);
    // sigprocmask(SIG_BLOCK, &newmask,0);
    // int a[10] = {1,2,3,4,5,6};
    // for (int i = 0; i < 6; i++) {
    //     pthread_create(&preg, 0, devider, &a[i]);
    // }



    // server_sockfd = mx_create_sockl(port);

    
    // poll_set[0].fd = server_sockfd;
    // poll_set[0].events = POLLIN;
    // numfds++;
    

    // while(1) {
    //     kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     // kill(getpid(), SIGUSR1);
    //     sleep(3);
    // }
    while (1) {
        char ch;
        int fd_index;
        int nread;
        int timeout = (3 * 60 * 1000);
         
        printf("Waiting for client (%d total)...\n", numfds);

        rc = poll(server_info->poll_set, server_info->size_connekt, -1);
        //   if (rc == 0)
        //     {
        //     printf("  poll() timed out.  End program.\n");
        // }
        for(fd_index = 0; fd_index < numfds; fd_index++) {
            if(poll_set[fd_index].revents == 0)
                continue;
            if(poll_set[fd_index].revents != POLLIN) {
                printf("  Error! revents = %d\n", poll_set[fd_index].revents);
                end_server = 1;
            }
            if(poll_set[fd_index].fd == server_sockfd) {
                client_len = sizeof(client_address);
                client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)&client_len);

                if (client_sockfd < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("  accept() failed");
                    }
                }
            
                printf("  New incoming connection - %d\n", client_sockfd);
                poll_set[numfds].fd = client_sockfd;
                poll_set[numfds].events = POLLIN;
                numfds++;
            }
            else {
                rc = recv(poll_set[fd_index].fd, buffer, sizeof(buffer), 0);
                if (rc < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("  recv() failed");
                        close_conn = 1;
                    }
                }
                if (rc == 0) {
                    printf("  Connection closed\n");
                    close_conn = 1;
                }
                len = rc;
                printf("  %d bytes received\n", len);
            }
            if (close_conn) {
                close(poll_set[fd_index].fd);
                poll_set[fd_index].fd = -1;
                compress_array = 1;
            }
        }
        if (compress_array) {
            compress_array = 0;
            for (int i = 0; i < numfds; i++) {
                if (poll_set[i].fd == -1) {
                    for(int j = i; j < numfds; j++) {
                       poll_set[j].fd = poll_set[j+1].fd;
                    }
                i--;
                numfds--;
                }
            }
        }
        if (end_server) {
            break;
            printf("  Server Closed\n");
        }


    }

    for (int i = 0; i < numfds; i++) {
        if(poll_set[i].fd >= 0)
            close(poll_set[i].fd);
    }
}
*/