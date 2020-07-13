#include "client.h"
#include "defines_client.h"

gboolean mx_scale_changed (GtkRange *range, GtkScrollType scroll, 
                            gdouble value, void *data) {
    t_fmod_info *music = (t_fmod_info *)data;
    unsigned int position = 0;
    char *name = g_object_get_data(G_OBJECT(range), "name");
    char filepath[512];


    memset(filepath , 0, 512);
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);
    
    if (music->currentSound != NULL && strcmp(filepath, music->currentSound) == 0 && value <= 100) {
        position = (value * music->sound_len)/100;
        music->possition = position;
        printf("val_that i have  %f, pos = %d\n", value, position);
        if (position < music->sound_len)
            FMOD_Channel_SetPosition(music->channel, position, FMOD_TIMEUNIT_PCM);

    }
    return FALSE;
}
