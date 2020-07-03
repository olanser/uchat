#include "client.h"
#include "libmx.h"

t_msg* mx_get_msg_from_resp(char *resp, t_info *info) {
    t_msg *msg = malloc(sizeof(t_msg));

    msg->msg_id = *(int*)&resp[9];
    msg->msg_id_chat = *(int*)&resp[13];
    msg->msg_id_user = *(int*)&resp[17];
    msg->msg_avatar = *(int*)&resp[41];
    msg->msg_type = *(int*)&resp[42];
    msg->msg_widget = mx_get_msg_widget(resp, info);
    msg->msg_time = mx_strdup(&resp[21]);
    msg->msg_data = mx_strdup(&resp[46]);
    return msg;
}
