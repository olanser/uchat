#include "client.h"

static char *get_format(char *str) {
    int n = mx_get_char_index(str, ':');
    char *format = mx_strndup(str, n);
    return format;
}

static char *get_string(char *str) {
    int n = mx_get_char_index(str, ':');
    char *string = mx_strndup(&str[n + 1], mx_strlen(str) - n);
    return string;
}

/* 
* get string with attributes
* from uchat_str
* ex: s i => <s><i></i></s> 
*/
static char *get_pango_attributes(char **attributes) {
    int i = -1;
    char *attributes_str = 0;
    char *att_buff = mx_strdup("");

    while (attributes[++i]) {
        if (attributes[i][0] == '#') { // color
            asprintf(&attributes_str, "<span foreground=\"%s\">%s</span>",attributes[i], att_buff);
        }
        else {
            asprintf(&attributes_str, "<%s>%s</%s>", attributes[i], att_buff, attributes[i]);
        }
        free(att_buff);
        att_buff = attributes_str;
    }
    return attributes_str;
}


static int get_index_of_str(char *pango_attr) {
    int i = -1;

    if (pango_attr == 0)
        return 0;
    while (pango_attr[++i]) {
        if (pango_attr[i] == '<' && pango_attr[i + 1] == '/') {
            return i;
        }
    }
    return 0;
}


/*
* get formated string in pango
* from uchat attributes and string of msg
*/
static char* get_pango(char **attributes, char *string) {
    char *pango = 0;
    char *pango_atributes = get_pango_attributes(attributes);
    int index = get_index_of_str(pango_atributes);

    pango = mx_str_insert(pango_atributes, string, index);
    free(pango_atributes);
    return pango;
}

/*
* get formated string with pango 
* from uchat
*/
char *mx_get_pango_from_uchat(char *uchat_format) {
    char *format = get_format(uchat_format);
    char **attributes = mx_strsplit(format, ' ');
    char *uchat_string = get_string(uchat_format);
    char *pango_str = get_pango(attributes, uchat_string);

    // pango_str = get_pango_str(uchat_format);
    printf("uchat str = %s\n", uchat_format);
    printf("  uchat format = %s\n", format);
    printf("  uchat string = %s\n", uchat_string);
    printf("  pango string = %s\n", pango_str);
    free(format);
    free(uchat_string);
    mx_del_strarr(&attributes);
    return pango_str;
}