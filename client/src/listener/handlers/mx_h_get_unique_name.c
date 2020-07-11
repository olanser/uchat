#include "client.h"

/* get first file in list without unique name */
t_file* get_file_without_uniq_name(t_list *list) {
    t_list *tmp = list;

    while (tmp) {
        if (((t_file*)tmp->data)->unique_name == 0)
            return ((t_file*)tmp->data);
        tmp = tmp->next;
    }
    return 0;
}

int mx_h_get_unique_name(char *response, t_info *info) {
    t_file *file = 0;
    
    printf(" mx_h_get_unique_name = 0\n");
    pthread_mutex_lock(&info->m_file_list);
    file = get_file_without_uniq_name(info->list_of_files);
    pthread_mutex_unlock(&info->m_file_list);
    if (file == 0) {
        return 1;
    }
    file->unique_name = *(long long *)&response[9];
    kill(getpid(), SIGUSR1); // new file sending
    return 0;
}
