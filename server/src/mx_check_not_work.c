#include "header.h"

bool mx_check_not_work(t_server_users user) {
    bool if_work = true;

    pthread_mutex_lock(&(user.m_if_work));
    if (user.work)
        if_work = false;
    pthread_mutex_unlock(&(user.m_if_work));
    return if_work;
}
