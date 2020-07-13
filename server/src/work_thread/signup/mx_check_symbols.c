#include "server.h"
#include "defines.h"

int mx_check_symbols(t_table_user *tuser) {
    if (mx_is_allowed_name(tuser->first_name) == false) {
        fprintf(MX_ERROR_THREAD, "error: not allowed first name\n");
        return 1;
    }
    if (mx_is_allowed_name(tuser->second_name) == false) {
        fprintf(MX_ERROR_THREAD, "error: not allowed second name\n");
        return 1;
    }
    if (mx_is_allowed_name(tuser->nickname) == false) {
        fprintf(MX_ERROR_THREAD, "error: not allowed nickname\n");
        return 1;
    }
    return 0;
}
