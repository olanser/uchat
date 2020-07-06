#include "client.h"
#include "libmx.h"

t_msg* mx_get_msg_from_resp(char *resp, t_info *info) {
    t_msg *msg = malloc(sizeof(t_msg));

    msg->msg_id = *(int*)&resp[9];
    msg->msg_id_chat = *(int*)&resp[13];
    msg->msg_id_user = *(int*)&resp[17];
    msg->msg_avatar = *(int*)&resp[41];
    msg->msg_type = *(int*)&resp[42];
    msg->msg_time = mx_strdup(&resp[21]);
    msg->msg_data = 0;
    msg->msg_f_name_of_file = 0;
    msg->msg_f_size = 0;
    msg->msg_f_type = 0;
    if (msg->msg_type == 3) {
        msg->msg_f_name_of_file = mx_strdup(&resp[46]);
        msg->msg_f_type = resp[302];
        msg->msg_f_size = *(int*)&resp[303];
        printf("size = %d\n", *(int*)&resp[303]);
    }
    else
    {
        msg->msg_data = mx_strdup(&resp[46]);
    }
    msg->msg_widget = mx_get_msg_widget(resp, info, msg);
    return msg;
}
