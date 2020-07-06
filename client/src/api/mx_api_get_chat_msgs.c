/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, int* mas, int query_id, int size) {
    query[0] = 12;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    *(int*)(&query[9]) = mas[0];
    *(int*)(&query[13]) = mas[1];
    *(int*)(&query[17]) = mas[2];
    return 0;
}

int mx_api_get_chat_msgs(int id_chat, int last_msgs_id, int count, t_info *info) {
    int size = 21;
    char *query = malloc(sizeof(char) * size);
    int mas[3] = {id_chat, last_msgs_id, count};

    memset(query, 0, size);
    get_query(query, mas, info->query_id, size);
    mx_tsend_msg_(info->sock, query, size, info);
    return 0;
}
