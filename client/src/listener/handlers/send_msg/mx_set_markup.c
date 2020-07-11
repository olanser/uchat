#include "client.h"
#include "defines_client.h"

char* get_markup(char *string) {
    char *substr = 0;
    int start = 0;
    int end = 0;
    int i = 0;
    char *markup = mx_strdup(string);

    while (1) {
        substr = mx_get_formated_substr(markup, &i, &start, &end);
        if (substr == 0)
            break;
        if (mx_is_substr_valid(substr)) {
            markup = mx_insert_str_between3(start, end, markup, 
                                            mx_get_pango_from_uchat(substr));
        }
        free(substr);
    }
    return markup;
}


void mx_set_markup(GtkWidget *label, char *str) {
    char *markup = get_markup(str);

    gtk_label_set_markup (GTK_LABEL (label), markup);
    free(markup);
}
