/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int id_user, int query_id, int size) {
    query[0] = 15;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = id_user;
    return 0;
}

int mx_api_create_dialog(int id_user, t_info *info) {
    int size = 13;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, id_user, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
