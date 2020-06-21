/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, char **parameters, int query_id) {
    query[0] = 1;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = (int)211;
    memcpy(&query[9], parameters[0], mx_strlen(parameters[0]));
    memcpy(&query[110], parameters[1], mx_strlen(parameters[1]));
    return 0;
}

/* 
* parameters[0] = nickname
* parameters[1] = password
*/
int mx_api_signin(char **parameters, t_info *info) {
    char *query = malloc(sizeof(char) * 211);
    memset(query, 0, 211);

    get_query(query, parameters, info->query_id);
    mx_tsend_msg(info->sock, query, 211);
    return 0;
}
