#include "server.h"

bool mx_check_avatar(char avatar) {
    if (avatar > 100)
        return false;
    return true;
}
