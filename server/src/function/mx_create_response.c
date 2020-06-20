#include "header.h"

char *mx_create_response(char id_request, int query, char status) {
    char *response = malloc(sizeof(char) * 10);

    response[0] = id_request;
    *(int*)&response[1] = query;
    *(int*)&response[5] = 10;
    response[9] = status;
    return response;
}
