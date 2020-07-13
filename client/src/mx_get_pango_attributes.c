/* 
* get string with attributes
* from uchat_str
* ex: s i => <s><i></i></s> 
*/
#include "client.h"

char *mx_get_pango_attributes(char **attributes) {
    int i = -1;
    char *attributes_str = 0;
    char *att_buff = mx_strdup("");

    while (attributes[++i]) {
        if (attributes[i][0] == '#') { // color
            asprintf(&attributes_str, "<span foreground=\"%s\">%s</span>",
                     attributes[i], att_buff);
        }
        else {
            asprintf(&attributes_str, "<%s>%s</%s>", attributes[i], att_buff,
                     attributes[i]);
        }
        free(att_buff);
        att_buff = attributes_str;
    }
    return attributes_str;
}
