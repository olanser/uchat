#include "client.h"
#include "mxinet.h"

static bool check_port(char *port) {
    int i = -1;

    while(port[++i]) {
        if (port[i] < 48 || port[i] > 57)
            return false;
    }
    return true;
}

static unsigned int check_connect(int argc, char **argv) {
    unsigned int ip = 0;

    if ((argc != 3)) {
        fprintf(stderr, "usage: ./uchat [ip of server] [port]\n");
        exit(1);
    }
    if ((ip = inet_aton(argv[1], 0)) == 0) {
        fprintf(stderr, "unvalid IP\n");
        exit(1);
    }
    if (!check_port(argv[2])) {
        fprintf(stderr, "unvalid port\n");
        exit(1);
    }
    return ip;
}

static void init_ssl(void) {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
}

void mx_connect(t_info *info, int argc, char **argv) {
    const SSL_METHOD *method;
    
    check_connect(argc, argv);
    info->sock = mx_create_tcp_csock(atoi(argv[2]), argv[1]);
    init_ssl();
    method = TLS_client_method();
    info->ctx = SSL_CTX_new(method);
    if (info->ctx == NULL ) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    info->ssl = SSL_new(info->ctx);
    SSL_set_fd(info->ssl, info->sock);
    if (SSL_connect(info->ssl) == 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(info->ssl);
        close(info->sock);
        exit(1);
    }
}
