/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int size, void **parameters, int query_id) {
    query[0] = 22;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = *(int*)parameters[0];
    *(int*)(&query[13]) = *(int*)parameters[1];
    *(int*)(&query[17]) = *(int*)parameters[2];
    *(int*)(&query[21]) = *(int*)parameters[3];
    return 0;
}

/* 
* parameters[0] = chat_id(4)
* parameters[1] = id_msg_of_file(4)
* parameters[2] = position_in_file(8)
* parameters[3] = count_bytes(4)
*/
int mx_api_get_file(void **parameters, t_info *info) {
    int size = 25;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, size, parameters, info->query_id);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
