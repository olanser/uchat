#include "server.h"
#include "defines.h"

int mx_do_query(char *sql, int (*callback)(void*,int,char**,char**),
                void *param, t_server *server_info) {
    int a;
    char *err = 0;
    char log[1024];

    pthread_mutex_lock(&(server_info->m_edit_database));
    a = sqlite3_exec(server_info->db, sql, callback, param, &err);
    if (a != SQLITE_OK) {
        sprintf(log, "error: database query: %s\n SQL = %s\n", err, sql);
        sqlite3_free(err);
        mx_add_log(server_info, log);
    }
    pthread_mutex_unlock(&(server_info->m_edit_database));
    return a;
}
