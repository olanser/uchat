#include "client.h"
#include "defines_client.h"

static void get_user(t_user_info* uinfo, char* response) {
    uinfo->avatar = 1;
    uinfo->frst_name = 0; 
    uinfo->scnd_name = 0;
    uinfo->id = *(int*)&response[10];
}

gboolean signup(void *data) {
    t_info *info = (t_info*)((void**)data)[0];
    char *response = (char*)((void**)data)[1];

    if (response[9] == (char)200) {
        get_user(info->user_info, response);
        mx_set_profile_window(info);
        mx_chang_scene(info, MX_SCENE_MAIN_CHAT);
        mx_api_get_chats_info(info);
    }
    else {
        mx_create_file_registration(0, 0);
    }
    free(response);
    free(data);
    return false;
}

int mx_h_signup(char *response, t_info *info) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = info;
    data[1] = malloc(*(int*)&response[5]);
    memcpy(data[1], response, *(int*)&response[5]);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, signup, data, 0);
    return 0;
}
