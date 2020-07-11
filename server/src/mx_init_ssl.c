#include "server.h"
#include "defines.h"

void mx_loadcertificates(SSL_CTX* ctx, char* certfile, char* keyfile) {
    if ( SSL_CTX_use_certificate_file(ctx, certfile, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    if ( SSL_CTX_use_PrivateKey_file(ctx, keyfile, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    if (!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr, "Private key does not match the public certificate\n");
        exit(1);
    }
}

void mx_init_ssl(t_server *server_info) {
    const SSL_METHOD *method;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = TLS_server_method();
    server_info->ctx = SSL_CTX_new(method);
    if (server_info->ctx == 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    mx_loadcertificates(server_info->ctx, MX_FILE_SERT, MX_FILE_KEY);
}