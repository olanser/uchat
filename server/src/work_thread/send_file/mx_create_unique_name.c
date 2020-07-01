#include "server.h"
#include "defines.h"

static void build_req(char **response, char *request) {
    *response[0] = request[0];
    *((int*)&(*response)[1]) = *(int*)&request[1];
    *((int*)&(*response)[5]) = 10;
    //response[9] = ;
}

char *mx_create_unique_name(t_server *server_info, t_server_users *user) {
    char *response = NULL;
    char *request = user->buff;

    time_t seconds;

    printf("Seconds since January 1, 1970 = %ld\n", seconds);

    int sec = (int) seconds;

    printf("int  %ld\n", sec);

    unsigned int secs = (unsigned int) seconds;

    printf("unsignet  %ld\n", secs);
   
    return 0;
}
