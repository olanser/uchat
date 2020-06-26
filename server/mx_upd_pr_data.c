#include "header.h"

int mx_upd_pr_data(char* user_id) {
    char *pid = mx_itoa(getpid());
    char sql[1024];
    
    if (user_id < 0)
        return 1;
    sprintf(sql, "insert into pd values(NULL, %s, %s, datetime('now'));", user_id, pid );
    return mx_do_query(sql, 0, 0);
}