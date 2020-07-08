#include "client.h"

t_file *mx_get_file_by_msg_id(t_list *list, int id) {
    t_list *tmp = list;

    while (tmp) {
        if (((t_file*)tmp->data)->msg_of_file->msg_id == id)
            return (t_file*)tmp->data;
        tmp = tmp->next;
    }
    return 0;
}
