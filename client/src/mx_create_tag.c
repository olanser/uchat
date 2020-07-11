#include "client.h"

t_tag* mx_create_tag(char *uchat_f, char *pango_f, int start, int end) {
    t_tag* tag = malloc(sizeof(t_tag));
    tag->end = end;
    tag->start = start;
    tag->pango = pango_f;
    tag->uchat = uchat_f;
    return tag;
}
