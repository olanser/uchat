/* 
* author vbalachevs
*/
#include "mxinet.h"
#include "client.h"
#include "libmx.h"

static int get_query(char *query, void **parameters, int query_id, int size) {
    query[0] = 21;
    *(int*)(&query[1]) = query_id;
    *(int*)(&query[5]) = size;
    query[9] = *(char*)parameters[0];
    *(int*)(&query[10]) = *(int*)parameters[1];
    *(int*)(&query[14]) = *(int*)parameters[2];
    printf("parameters[3] = %s\n", parameters[3]);
    mx_strcpy(&query[19], parameters[3]);
    *(long long*)(&query[275]) = *(long long*)parameters[4];
    printf("avatar2 = %d\n", *(char*)parameters[5]);
    query[284] = *(char*)parameters[5];
    return 0;
}

/* 
* parameters[0] = filetype(1)
* parameters[1] = size_of_file(4)
* parameters[2] = id_chat(4)
* parameters[3] = name(255)\0
* parameters[4] = unique name(8)
* parameters[5] = avatar(1) 
*/
int mx_api_end_send_file(void **parameters, t_info *info) {
    int size = 285;
    char *query = malloc(sizeof(char) * size);
    memset(query, 0, size);

    get_query(query, parameters, info->query_id, size);
    printf("query[0] = %d\n", query[0]);
    mx_send_msg_(info->sock, query, size, info);
    printf("SENDED // api_end_send_file\n");
    free(query);
    return 0;
}