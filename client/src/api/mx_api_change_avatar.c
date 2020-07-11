/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int avatar, int query_id, int size) {
    query[0] = 18;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = avatar;
    return 0;
}

int mx_api_change_avatar(int avatar, t_info *info) {
    int size = 13;
    char *query = malloc(sizeof(char) * size);

    memset(query, 0, size);
    get_query(query, avatar, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
