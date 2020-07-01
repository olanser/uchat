#include "client_unit.h"
#include "libmx.h"

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

void mx_editmsg(t_info* info) {
    char buff[1024];
    int size = 42;

    memset(buff, 0, size);
    buff[0] = 3;
    *(int*)&buff[5] = size;
    *(int*)&buff[9] = 1; //id_chat 
    *(int*)&buff[13] = 7; //id_msg
    buff[17] = info->avatar;
    sprintf(&buff[18], "dawawdawd3234"); //data end \0;
    write(info->socket, buff, size);
}


int main(int argc, char *argv[]) {
    int size = 1;
    t_info **box_info =  malloc(sizeof(t_info*) * size);
    char buff[1024];

    for (int i = 0; i < size; i++) {
        box_info[i] = mx_get_info();
        mx_signin(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (buff[9] != (char)200) {
            printf("Status = %d\n", buff[9]);
            return 1;
        }
        box_info[i]->id_user = *((int*)&buff[10]);
        box_info[i]->avatar = buff[217];
        printf("ID user = %d and AVATAR = %d and SIZE = %d\n", box_info[i]->id_user,box_info[i]->avatar, *(int*)&buff[5]);
        // printf("ID user = %s and AVATAR = %d\n", box_info[i]->id_user,  box_info[i]->avatar);
    }
    for (int i = 0; i < size; i++) {
        mx_editmsg(box_info[i]);
    }
    for (int i = 0; i < size; i++) {
        while(1) {
        read(box_info[i]->socket, buff, 9);
        read(box_info[i]->socket, &buff[9], *(int*)&buff[5] - 9);
        if (*(int*)&buff[5] < 44) {
            printf("ERROR response %d status = %d!! size %d\n", buff[0], buff[9], *(int*)&buff[5]);
            return 1;
        }
        if (!(buff[0] == 2 || buff[0] == 3)) {
            printf("ERROR API %d!!", buff[0]);
            return 1;
        }
        printf("API = %d, ID msg = %d, ID chat = %d, ID user = %d, TIME = %s, AVATAR = %d, MSG = %s\n",
            buff[0], *((int*)&buff[9]), *((int*)&buff[13]), *((int*)&buff[17]), &buff[21], buff[41], &buff[42]);
        }
    }
    for (int i = 0; i < size; i++)
        close(box_info[i]->socket);
    printf("OK\n");
    return 0;
}
