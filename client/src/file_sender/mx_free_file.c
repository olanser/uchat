#include "client.h"
#include "mxinet.h"
#include "defines_client.h"

void mx_free_file(t_file *file) {
    free(file->name);
    free(file);
}
