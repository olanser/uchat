#include "server.h"

int mx_callback_count(void *data, int column, char **name, char **tabledata) {
    *((int*)data) += 1;
    return 0;
}

int mx_return_one_str(void *param, int column, char **data, char **names) {
    *((char **)param) = mx_strdup(data[0]);

    return 0;
}
