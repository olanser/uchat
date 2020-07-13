#include "openssl/sha.h"
#include "client.h"

char *mx_hash(const char *pass, const char *log) {
    SHA512_CTX ctx;
    unsigned char *hash = malloc(sizeof(unsigned char) * 64);
    char *temp = mx_strjoin(pass, log);

    if (!SHA512_Init(&ctx)) {
        printf("Can not init hash\n");
        exit(1);
    }
    if (!SHA512_Update(&ctx, temp, strlen(temp))) {
        printf("Can not update hash\n");
        exit(1);
    }
    if (!SHA512_Final(hash, &ctx)) {
        printf("Can not final hash\n");
        exit(1);
    }
    free(temp);
    return (char*)hash;
}
