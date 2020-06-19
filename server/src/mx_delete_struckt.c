#include "header.h"
#include "mxinet.h"
#include "defines.h"

void mx_del_user_info(t_server_users *table_users) {
    if (table_users->buff != NULL)
        mx_strdel(&(table_users->buff));
    table_users = NULL;
}
