#include "client.h"
#include "mxinet.h"

static sigset_t set_mask(void) {
    sigset_t newmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    return newmask;
}

t_file* get_file_with_uniq_name(t_list **list) {
    t_list *tmp = *list;

    if (*list == 0)
        return 0;
    if (((t_file*)tmp->data)->unique_name != 0) {
        *list = (*list)->next;
        return ((t_file*)tmp->data);
    }
    while (tmp->next) {
        if (((t_file*)tmp->next->data)->unique_name != 0) {
            tmp->next = tmp->next->next;
            return ((t_file*)tmp->data);
        }
            
        tmp = tmp->next;
    }
    return 0;
}

static void send_end_file(t_info *info, t_file *file) {
    int type = 0;
    void *parameters[6] = {&type, 
        &file->size, 
        &file->chat_id, 
        file->name, 
        &file->unique_name, 
        &info->user_info->avatar};
    mx_api_end_send_file(parameters, info);
}

void mx_free_file(t_file *file) {
    free(file->name);
    free(file);
}

static void get_head(char *buff, t_file *file, t_info *info) {
    // memset(buff, 0, 1024);
    buff[0] = 20;
    *(int*)&buff[1] = info->query_id;
    *(int*)&buff[5] = 1024;
    *(long long*)&buff[9] = file->unique_name;
}

void write_file(t_info *info) {
    t_file *file = 0; // LEAK
    char buff[1024];
    int count  = 0;

    memset(buff, 0, 1024);
    pthread_mutex_lock(&info->m_file_list);
    file = get_file_with_uniq_name(&info->list_of_files);
    pthread_mutex_unlock(&info->m_file_list);
    if (file == 0)
        return;
    get_head(buff, file, info);
     while((count = read(file->fd, &buff[18], 1006))) {
        *((int*)&buff[5]) = 18 + count;
        mx_send_msg_(info->sock, buff, count + 18, info);
    }
    send_end_file(info, file);
    mx_free_file(file);

    if (info->list_of_files != 0)
        write_file(info);
}

void *mx_thread_send_file(void *data) {
    t_info *info = (t_info*)data;
    mx_init_signals();
    sigset_t newmask = set_mask();
    int signo;
    
    while (1) {
        sigwait(&(newmask), &signo);
        write_file(info);
    }
    return (void*)0;
}
