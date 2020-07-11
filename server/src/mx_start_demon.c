#include "server.h"

static void change_fd(t_server *server_info) {
    int fd = open("database/log2.txt", O_RDWR | O_APPEND | O_CREAT , S_IRWXU);
    int fds[3];

    if (fd == -1) {
        mx_add_log(server_info, "ERROR OPEN LOG2 FILE\n");
        exit(1);
    }
    close(0);
    close(1);
    close(2);
    fds[0] = open("/dev/null", O_RDWR);
    fds[1] = dup(fd);
    fds[2] = dup(fd);
    if (fds[0] != 0 && fds[1] != 1 && fds[2] != 2) {
        mx_add_log(server_info, "ERROR FD!!!\n");
        exit(1);
    }
    close(fd);
}

static void fork_work(t_server *server_info) {
    pid_t pid = fork();

    if (pid < 0) {
        mx_add_log(server_info, "ERROR FORK!!!\n");
        exit(1);
    }
    else if (pid != 0) {
        exit(0);
    }
}

void mx_start_demon(t_server *server_info) {
    struct sigaction sa;
    int fds[3];

    fork_work(server_info);
    setsid();
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        mx_add_log(server_info, "ERROR IGNOR SIGHUP\n");
        exit(1);
    }
    fork_work(server_info);
    change_fd(server_info);
}
