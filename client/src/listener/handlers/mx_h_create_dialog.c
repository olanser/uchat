#include "client.h"

static bool check(char *response, t_info *info) {
    if ((*(int*)&response[5] < 10) 
        || mx_is_chat_exist(*(int*)&response[10], info->list_of_chats)) {
        return false;
    }
    return true;
}

int mx_h_create_dialog(char *response, t_info *info) {
    if (check(response, info) == false) 
        return 1;
    mx_api_get_chat_info(*(int*)&response[9], info);
    return 0;
}
