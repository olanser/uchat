#include "client.h"

static t_user_info* get_user(t_info* info, char* response) {
    t_user_info* uinfo = malloc(sizeof(t_user_info));
    uinfo->avatar = '4';
    uinfo->frst_name = 0; 
    uinfo->nickname = 0;
    uinfo->scnd_name = 0;
    uinfo->id = *(int*)&response[10];
    return uinfo;
}

int mx_h_signup(char *response, t_info *info) {
    if (response[9] == (char)200) {
        info->user_info = get_user(info, response);
    }
    else {
        // NOT REGISTERED
        mx_create_file_registration(0, 0);
        printf("SIGNIN ERR STATUS = %d\n", response[9]);
    }
    return 0;
}
