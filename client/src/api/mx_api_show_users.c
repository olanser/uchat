/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, char *parameter, int query_id, int size) {
    query[0] = 9;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    memcpy(&query[9], parameter, mx_strlen(parameter));
    return 0;
}

/* 
* parameters[0] = user id(10)
*/
int mx_api_show_users(char *str, t_info *info) {
    int size = 9 + mx_strlen(str) + 1;
    char *query = malloc(sizeof(char) * size);

    memset(query, 0, size);
    get_query(query, str, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
