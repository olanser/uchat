/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, void **parameters, int query_id, int size) {
    query[0] = 2;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = *(char*)parameters[0];
    *(int*)(&query[14]) = *(int*)parameters[2];; // type - msg
    memcpy(&query[18], parameters[1], mx_strlen((char*)parameters[1]));
    return 0;
}

/* 
* parameters[0] = chat id(10)
* parameters[1] = data
* type: 1 - msg; 2 - sticker
*/
int mx_api_send_message(int chat_id, char *msg, int type, t_info *info) {
    int size = 18 + mx_strlen(msg) + 1;
    char *query = malloc(sizeof(char) * size);
    void *parameters[3] = {&chat_id, msg, &type};

    memset(query, 0, size);
    query[13] = info->user_info->avatar;
    get_query(query, parameters, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
