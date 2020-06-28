#include "client_unit.h"

static void set_sockaddr(struct sockaddr_in *addr, int port) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_aton("63.161.169.137", &myaddr.sin_addr.s_addr);
}

int mx_create_sock(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock == -1) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        exit(1);
    }
    struct sockaddr_in addr;
    set_sockaddr(&addr, port);
    if (connect(sock, (struct sockaddr*)&addr,sizeof(addr)) == -1) {
        fprintf(stderr, "connect error: %s\n", strerror(errno));
        exit(1);
    }
    
    return sock;
}

t_info *mx_get_info() {
    t_info *info = malloc(sizeof(t_info));

    info->socket = mx_create_sock(MX_PORT);
    return info;
}

void mx_signin(t_info* info) {
    char buff[1024];

    memset(buff, 0, 211);
    buff[0] = 1;
    *(int*)&buff[5] = 211;
    sprintf(&buff[9], "%s", "asd");
    sprintf(&buff[110], "%s", "asd");
    write(info->socket, buff, 211);
}

void mx_get_chat_msg(t_info* info) {
    char buff[1024];
    int size = 35;

    memset(buff, 0, size);
    buff[0] = 12;
    *(int*)&buff[5] = size;
    buff[9] = '1'; //id_chat
    buff[20] = '0';
    *(int*)&buff[31] = 5;
    write(info->socket, buff, size);
}

int main(int argc, char *argv[]) {
    t_info **box_info =  malloc(sizeof(t_info*) * 100);
    char buff[1024];
    int size = 1;

    for (int i = 0; i < size; i++) {
        box_info[i] = mx_get_info();
        mx_signin(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (buff[9] != (char)200)
            return 1;
    }
    for (int i = 0; i < size; i++) {
        mx_get_chat_msg(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        while(1) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (*(int*)&buff[5] < 65) {
            printf("ERROR response %d status = %d!! size %d\n", buff[0], buff[9], *(int*)&buff[5]);
            return 1;
        }
        if (!(buff[0] == 2 || buff[0] == 3)) {
            printf("ERROR API %d!!", buff[0]);
            return 1;
        }
        printf("API = %d, ID msg = %s, ID chat = %s, ID user = %s, TIME = %s, AVATAR = %d, MSG = %s\n",
            buff[0], &buff[9], &buff[20], &buff[31], &buff[42], buff[62], &buff[63]);
        }
    }
    for (int i = 0; i < size; i++)
        close(box_info[i]->socket);
    printf("OK\n");
    return 0;
}
