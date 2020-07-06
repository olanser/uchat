/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int user_id, int query_id, int size) {
    query[0] = 6;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = user_id;
    return 0;
}

/* 
* parameters[0] = user id(10)
*/
int mx_api_get_user_info(int user_id, t_info *info) {
    int size = 13;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, user_id, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
