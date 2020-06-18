#include "header.h"

void mx_create_response(void *request, char **response) {
    *response = malloc(sizeof(char) * 10);
    mx_memcpy(*response,  request, 5);
    (*response)[5] = (char)10;
    (*response)[6] = 0;
    (*response)[7] = 0;
    (*response)[8] = 0;
}