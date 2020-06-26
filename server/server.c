#include "header.h"
#include "mxinet.h"



void registration(void) {
    int sockL = mx_create_sockl(MX_PORT);
    struct sockaddr addr;
    socklen_t len = sizeof(addr);

    while (1) {
        int new_sock = accept(sockL, &addr,&len);

        if (new_sock == -1) {
            fprintf(stderr, "accept error: %s\n", strerror(errno));
            exit(1);
        }
        if (fork() == 0) {
            printf("Pid children: %d\n", getpid());
            serve(new_sock);
            exit(0);
        }
        close(new_sock);
        printf("Pid: %d\n", getpid());
        printf("Connected: %d %d\n", ((struct sockaddr_in*)&addr)->sin_addr.s_addr, ((struct sockaddr_in*)&addr)->sin_port);
    }
    return;
}


void* waitchildren(void *data) {
    while (1) {
        wait(0);
    }
    return (void*)0;
}

void exitchild(void) {
    char sql[1024];

    if (getpgid(getpid())== getpid()) {
        sprintf(sql, "delete from pd;");
    }
    else
        sprintf(sql, "delete from pd where pd_pid = %s;", mx_itoa(getpid()));
    mx_do_query(sql,0,0);
    // kill(-getpid(), SIGINT);
    return;
}
void signal_stop(int sig) {
    exit(0);
}

// int main() {
//     pthread_t preg;
//     sigset_t newmask;

//     sigemptyset(&newmask);
//     sigaddset(&newmask, SIGUSR1);
//     sigprocmask(SIG_BLOCK, &newmask,0);
//     signal(SIGINT, signal_stop);
//     atexit(exitchild);
//     pthread_create(&preg, 0, waitchildren, 0);
//     registration();
//     pthread_join(preg, 0);
// }

#define POLL_SIZE 32

void *devider(void *data) {
    int i = *((int*)data);
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    int signo;
    while (1) {
        sigwait(&(newmask), &signo);

        printf("treads = %d\n", i);
        return 0;
        usleep(1000);
        // sleep(10);
    }
    return 0;
}

int main() {
    struct pollfd poll_set[POLL_SIZE];
    int numfds = 0;
    int max_fd = 0;
    bool end_server = 0;
    bool close_conn = 0;
    bool compress_array = 0;
    pthread_t preg;
    sigset_t newmask;

    struct sockaddr client_address;
    int client_len;
    int client_sockfd;
    int nread;
    int rc = 0;

    char buffer[1024];
    int len;

    int server_sockfd = 0;






    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &newmask,0);
    int a[10] = {1,2,3,4,5,6};
    for (int i = 0; i < 6; i++) {
        pthread_create(&preg, 0, devider, &a[i]);
    }



    server_sockfd = mx_create_sockl(MX_PORT);

    
    poll_set[0].fd = server_sockfd;
    poll_set[0].events = POLLIN;
    numfds++;
    

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

        rc = poll(poll_set, numfds, -1);
          if (rc == 0)
            {
            printf("  poll() timed out.  End program.\n");
        }
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
