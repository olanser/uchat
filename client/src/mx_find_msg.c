#include "client.h"
#include "libmx.h"

t_msg* mx_find_msg(t_list *chat_list, int msg_id, int chat_id) {
    t_msg *msg = 0;
    t_chat_info *chat = mx_get_chat_info(chat_list, chat_id);

    if (chat == 0)
        return 0;
    msg = mx_get_msg_by_id(chat->msgs, msg_id);
    return msg;
}
