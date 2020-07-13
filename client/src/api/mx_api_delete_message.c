/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int *parameters, int query_id, int size) {
    query[0] = 4;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = parameters[0];
    *(int*)(&query[13]) = parameters[1];
    return 0;
}

int mx_api_delete_message(int id_msg, int id_chat, t_info *info) {
    int size = 17;
    char *query = malloc(sizeof(char) * size);
    int parameters[2] = {id_msg, id_chat};

    memset(query, 0, size);
    get_query(query, parameters, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
