#include "header.h"

static char *create_new_message(char **name) {
    int sum =  strlen(name[4]) + 5 + 4 + 11 + 11 + 11 + 20 + 1;
    char *temp = mx_strnew(sum);

    temp[0] = name[5][0] - '0';
    *((int*)(&temp[5])) = sum + 1;
    mx_memcpy(&temp[9], name[0], strlen(name[0]));
    mx_memcpy(&temp[20], name[1], strlen(name[1]));
    mx_memcpy(&temp[31], name[2], strlen(name[2]));
    mx_memcpy(&temp[42], name[3], strlen(name[3]));
    mx_memcpy(&temp[62], name[6], 1);
    mx_memcpy(&temp[63], name[4], strlen(name[4]));
    printf("6 - %s\n", &temp[62]);

    return temp;
}
static char *create_new_file(char **name) {
    int sum =  strlen(name[8]) + 5 + 4 + 11 + 11 + 11 + 20 + 1 + 1 + 4;
    char *temp = mx_strnew(sum);

    temp[0] = name[5][0] - '0';
    *((int*)(&temp[5])) = sum + 1;
    mx_memcpy(&temp[9], name[0], strlen(name[0]));
    mx_memcpy(&temp[20], name[1], strlen(name[1]));
    mx_memcpy(&temp[31], name[2], strlen(name[2]));
    mx_memcpy(&temp[42], name[3], strlen(name[3]));
    mx_memcpy(&temp[62], name[6], 1);
    mx_memcpy(&temp[63], name[7], strlen(name[7]));
    *((int *)(&temp[64])) = atoi(name[9]);

    mx_memcpy(&temp[68], name[8], strlen(name[8]));

    return temp;
}

static char *delete_message(char **name) {
    int sum = 20;
    char *temp = mx_strnew(sum);

    temp[0] = name[5][0] - '0';
    *((int*)(&temp[5])) = sum + 1;
    mx_memcpy(&temp[9], name[0], strlen(name[0]));
    return temp;
}

static bool if_duplicate(char *time, char *id_msg, t_updates *updates) {
    t_list *list_id = updates->list_id;

     if (strcmp(time, updates->time) == 0) {
        while (list_id) {
            if (strcmp(list_id->data, id_msg) == 0)
                return 1;
            list_id = list_id->next;
        }
        mx_push_front(&(updates->list_id), mx_strdup(id_msg));
    }
    else if (strcmp(updates->time, time) < 0) {
        while (updates->list_id)
            mx_pop_front(&(updates->list_id));
        mx_push_front(&(updates->list_id), mx_strdup(id_msg));
        free(updates->time);
        updates->time = mx_strdup(time);
    }
    return 0;
}

int mx_callback_updates(void *data, int columns, char **name, char **tabledata) {
    char * (*new_signal[])(char**) = {0,0,create_new_message, create_new_message, delete_message, create_new_file, 0};
    char *temp;
    int status = name[5][0] - '0';
    t_updates *updates = ((t_user *)data)->updates;
    t_user* info = data;

    if (status > 5)
        return 0;
    if (if_duplicate(name[3], name[0], updates))
        return 0;
    temp = new_signal[status](name);
    pthread_mutex_lock(&info->m_fd);
    write(info->socket, temp, *(int*)&temp[5]);
    pthread_mutex_unlock(&info->m_fd);
    return 0;
}
