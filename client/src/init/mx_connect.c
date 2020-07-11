#include "client.h"
#include "mxinet.h"

void mx_connect(t_info *info) {
    const SSL_METHOD *method;

    info->sock = mx_create_tcp_csock(2365, INADDR_LOOPBACK);
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
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
