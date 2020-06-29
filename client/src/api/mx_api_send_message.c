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
    *(int*)(&query[9]) = *(int*)parameters[0];
    *(int*)(&query[14]) = 1; // type - msg
    memcpy(&query[18], parameters[1], mx_strlen((char*)parameters[1]));
    return 0;
}

/* 
* parameters[0] = chat id(10)
* parameters[1] = data
*/
int mx_api_send_message(int chat_id, char *msg, t_info *info) {
    int size = 18 + mx_strlen(msg) + 1;
    char *query = malloc(sizeof(char) * size);
    void *parameters[2] = {&chat_id, msg};
    memset(query, 0, size);

    query[13] = info->user_info->avatar;
    get_query(query, parameters, info->query_id, size);
    mx_tsend_msg(info->sock, query, size);
    return 0;
}
