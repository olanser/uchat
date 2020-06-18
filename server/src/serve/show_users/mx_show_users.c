#include "header.h"

static int callback(void *data, int columns, char **name, char **tabledata) {
    int total_len = 11 + strlen(name[1]) + 1;
    char *temp = malloc(total_len);

    memset(temp, 0, total_len);
    mx_memcpy(temp, name[0], strlen(name[0]));
    mx_memcpy(&temp[11], name[1], strlen(name[1]));
    mx_push_front(data, temp);
    return 0;
}

static int len_request(t_list *head, char **response) {
    int len = 10;
    while (head) {
        len = len + 12 + strlen(&head->data[11]);
        head = head->next;
    }
    *response = malloc(len);
    *(int*)(&(*response)[5]) = len;
    return len;
}

int mx_show_users(void *request, char **response, t_user *user_info) {
    char *sql = mx_strjoin("select usr_id, usr_nickname from user where usr_nickname like '\%", &request[9]);
    // char sql[1024] = "a";
    t_list *head = 0;
    int len;
    int i = 10;
    int len_str;

    sql = mx_strjoin2(sql, "\%' limit 10;");
    mx_do_query(sql, callback, &head);
    len = len_request(head, response);
    mx_memcpy(*response, request, 5);
    if (head == 0)
        (*response)[9] = MQ_QS_NOT_FOUND;
    else
        (*response)[9] = (char)MX_QS_OK;
    while (head) {
        len_str = 12 + strlen(&head->data[11]); 
        mx_memcpy(&(*response)[i], head->data, len_str);
        i += len_str;
        mx_pop_front(&head);
    }
    return len;
}
