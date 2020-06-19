#include "header.h"

int mx_check_message(char *request, t_table_message *message) {
    int len = 0;

    message->id_query = &request[1];
    if (mx_check_number(&request[9], 11) == 0)
        return 0;
    message->id_chat = &request[9]; 
    message->size = *((unsigned int*)(&request[5]));
    message->data = &request[20];
    return 1;
}