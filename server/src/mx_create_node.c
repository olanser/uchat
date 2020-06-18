#include "header.h"

t_list *mx_create_node(void *data) {
    t_list *node = malloc(sizeof(t_list));

    node->data = data;
    node->next = 0;
    return node;
}
