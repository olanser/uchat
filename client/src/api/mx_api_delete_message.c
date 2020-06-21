/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, char **parameters, int query_id, int size) {
    query[0] = 4;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    memcpy(&query[9], parameters[0], mx_strlen(parameters[0]));
    memcpy(&query[20], parameters[1], mx_strlen(parameters[1]));
    return 0;
}

/* 
* parameters[0] = id msg(10)
* parameters[1] = id chat(10)
*/
int mx_api_delete_message(char **parameters, t_info *info) {
    int size = 31;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, parameters, info->query_id, size);
    mx_tsend_msg(info->sock, query, size);
    return 0;
}
