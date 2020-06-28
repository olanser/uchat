#include "server.h"

bool mx_check_avatar(char avatar) {
    if (avatar < 48 || avatar > 57)
        return false;
    return true;
}
