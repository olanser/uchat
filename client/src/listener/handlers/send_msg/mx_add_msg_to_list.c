#include "client.h"
#include "libmx.h"

/* add to list and return index*/
int mx_add_msg_to_list(t_list **list_, t_msg *msg) {
    t_list *list = *list_;
    t_list *new = 0;
    t_list *tmp = list;
    int i = 1;

    //if enmty or first less than new
    if (list == 0 || (((t_msg*)list->data)->msg_id > msg->msg_id)) {
        mx_push_front(list_, msg);
        return 0;
    }
    while (tmp->next && ((t_msg*)tmp->next->data)->msg_id < msg->msg_id) {
        i++;
        tmp = tmp->next;
    }
    new = mx_create_node(msg);
    new->next = tmp->next;
    tmp->next = new;
    return i;
}