#include "client.h"
#include "defines_client.h"

static int get_start_index(char *str, int start) {
    int i = start;

    while (str[i]) {
        if (str[i] == '%' && str[i + 1] == '%')
            return i + 2;
        i++;
    }
    return -1; // we at the end of string
}

static int get_end_index(char *str, int start) {
    int i = start;

    while (str[i]) {
        if (str[i] == '%' && str[i + 1] == '%')
            return i;
        i++;
    }
    return -1; // we at the end of string
}

/* 
* get substr in pattern %%[some data]%%
* starting with i index
* return 0 if substr no finded
*/
char *get_formated_substr(char *str, int *index, int *start_, int *end_) {
    char *substr = 0;
    int start = (*index);
    int end = (*index);

    if ((start = get_start_index(str, start)) == -1 
        || (end = get_end_index(str, start)) == -1)
        return 0;
    substr = mx_strndup(&str[start], end - start);
    *index = end;
    *start_ = start - 2;
    *end_ = end + 2;
    return substr;
}

static bool check_color(char *str) {
    int i = 0;

    printf("check color |%s|\n", str);
    for (int j = 0; j < 6; j++) {
        if (((str[++i] < 48) || (str[i] > 57)) // 0-10
            && ((str[i] < 65) || (str[i] > 70)) // A-F
            && ((str[i] < 97) || (str[i] > 102))) // a-f
            {
                printf("color false\n");
                return false;
            }
    }
    if (str[++i] != '\0') {
        printf("symbol false\n");
        return false;
    }
    return true;
}

static bool check_tags(char *str, int end_format) {
    char *format = mx_strndup(str, end_format);
    char **tags = mx_strsplit(format, ' ');
    int i = -1;

    printf("format = %s\n", format);
    free(format);
    
    while (tags[++i]) {
        if (tags[i][0] == '#') {
            if (!check_color(tags[i])) {
                mx_del_strarr(&tags);
                printf("unvalid 1\n");
                return false;
            }
        }
        else if (!(mx_strcmp(tags[i], "b") == 0 
                || mx_strcmp(tags[i], "big") == 0
                || mx_strcmp(tags[i], "i") == 0
                || mx_strcmp(tags[i], "s") == 0
                || mx_strcmp(tags[i], "sub") == 0
                || mx_strcmp(tags[i], "small") == 0
                || mx_strcmp(tags[i], "tt") == 0
                || mx_strcmp(tags[i], "u") == 0)) 
            {
                mx_del_strarr(&tags);
                printf("unvalid 2\n");
                return false;
            }
    }
    mx_del_strarr(&tags);
    return true;
}

bool is_substr_valid(char *substr) {
    int end = mx_get_char_index(substr, ':');
    
    if (end == -1) {// ':' dont finded
        printf(" ':' - dont finded\n");
        return false;
    }
    if (!check_tags(substr, end))
        return false;

    return true;
}

char *mx_insert_str_between(int start, int end, char*str, char*substr) {
    char *new_str = 0; // malloc(mx_strlen(str) - end + start + mx_strlen(substr));
    int len = 0;

    if (str == 0 && substr)
        mx_strdup(substr);
    if (substr == 0 && str)
        mx_strdup(str);
    if (substr == 0 && str == 0)
        mx_strdup("");
    len = mx_strlen(str) - end + start + mx_strlen(substr) + 1;
    new_str = malloc(len);
    memset(new_str, 0, len);
    memcpy(new_str, str, start);
    memcpy(&new_str[start], substr, mx_strlen(substr));
    memcpy(&new_str[start + mx_strlen(substr)], &str[end], mx_strlen(str) - end);
    return new_str;
}

char *mx_insert_str_between3(int start, int end, char*str_f, char*substr_f) {
    char *new_str = 0; // malloc(mx_strlen(str) - end + start + mx_strlen(substr));
    int len = 0;

    if (str_f == 0 && substr_f){
        new_str = mx_strdup(substr_f);
    }
    else if (substr_f == 0 && str_f)
        new_str = mx_strdup(str_f);
    else if (substr_f == 0 && str_f == 0)
        new_str = mx_strdup("");
    if (new_str) {
        printf("BB\n");
        free(str_f);
        free(substr_f);
        return new_str;
    } 
    printf("AA\n");
    len = mx_strlen(str_f) - end + start + mx_strlen(substr_f) + 1;
    new_str = malloc(len);
    memset(new_str, 0, len);
    memcpy(new_str, str_f, start);
    memcpy(&new_str[start], substr_f, mx_strlen(substr_f));
    memcpy(&new_str[start + mx_strlen(substr_f)], &str_f[end], mx_strlen(str_f) - end);
    free(str_f);
    free(substr_f);
    return new_str;
}

char* get_markup(char *string) {
    char *substr = 0;
    int start = 0;
    int end = 0;
    int i = 0;
    char *markup = mx_strdup(string);

    while (1) {
        substr = get_formated_substr(markup, &i, &start, &end);
        if (substr == 0)
            break;
        if (is_substr_valid(substr)) {
            markup = mx_insert_str_between3(start, end, markup, mx_get_pango_from_uchat(substr));
        }
        else {
            printf("unvalid\n");
        }
        free(substr);
    }
    
    printf("FINAL MARKUP = |%s|\n", markup);
    return markup;
}


void mx_set_markup(GtkWidget *label, char *str) {
    char *markup = get_markup(str);

    gtk_label_set_markup (GTK_LABEL (label), markup);
    free(markup);
}
