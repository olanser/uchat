#include "client.h"

t_user_info* mx_crete_user(t_info* info) {
    t_user_info* uinfo = malloc(sizeof(t_user_info));

    uinfo->avatar = 1; // response[217]
    uinfo->frst_name = 0; 
    uinfo->nickname = 0; // 116
    uinfo->scnd_name = 0;
    uinfo->id = 0; // *(int*)&response[10]
    return uinfo;
}