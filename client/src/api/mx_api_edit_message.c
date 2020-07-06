/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, void**data, int query_id, int size) {
    query[0] = 3;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = *(int*)data[0];
    *(int*)(&query[13]) = *(int*)data[1];
    memcpy(&query[18], (char*)data[2], mx_strlen((char*)data[2]));
    return 0;
}

int mx_api_edit_message(int id_chat, int id_msg, char *msg, t_info *info) {
    int size = 18 + mx_strlen(msg) + 1;
    char *query = malloc(sizeof(char) * size);
    void *parameters[3] = {&id_chat, &id_msg, msg};

    memset(query, 0, size);
    query[17] = info->user_info->avatar;
    get_query(query, parameters, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
