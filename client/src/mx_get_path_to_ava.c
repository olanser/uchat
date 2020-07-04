#include "icons.h"
#include "defines_client.h"

const char *mx_get_path_to_ava(int number) {
    static const char *mas[] = {
        MX_AVA_1,
        MX_AVA_2,
        MX_AVA_3,
        MX_AVA_4,
    };
    if (number > MX_MAX_AVA) {
        return mas[0];
    }
    return mas[number];
}