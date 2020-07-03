#include "client.h"
#include "libmx.h"

t_msg* mx_get_msg_by_id(t_list *list_msg, int msg_id) {
    t_list *tmp = list_msg;

    while (tmp) {
        if (((t_msg*)tmp->data)->msg_id == msg_id)
            return (t_msg*)tmp->data;
        tmp = tmp->next;
    }
    return 0;
}
