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
    if (music->currentSound != NULL 
        && strcmp(filepath, music->currentSound) == 0 && value <= 100) {
        position = (value * music->sound_len)/100;
        music->possition = position;
        if (position < music->sound_len)
            FMOD_Channel_SetPosition(music->channel, position, 
                                    FMOD_TIMEUNIT_PCM);
    }
    return FALSE;
}


void mx_unload(t_fmod_info *music) {
    FMOD_RESULT result;
    if (music->possible) {
        music->Sound_on = true;
        FMOD_Channel_SetPosition(music->channel, 0, FMOD_TIMEUNIT_PCM);
        result = FMOD_Sound_Release(music->sound);
        music->pause = false;
        music->sound = NULL;
        music->currentSound = NULL;
        music->scale = NULL;
        music->sound_len = 0;
        music->possition = 0;
        mx_strdel(&(music->sound_to_pay));
    }
}



void mx_load(t_fmod_info *music) {
    FMOD_RESULT result;

    music->currentSound = music->sound_to_pay;
    if (music->possible && music->Sound_on) {
        result = FMOD_Sound_Release(music->sound);
        result = FMOD_System_CreateStream(music->fmodsystem, 
                music->currentSound, FMOD_SOFTWARE, 0, &(music->sound));
        if (result != FMOD_OK) {
            music->possible = false;
        }
    }
}

void mx_stop_btn(GtkButton *btn, void*data) {
    t_fmod_info *music = (t_fmod_info *)data;
    char *name = g_object_get_data(G_OBJECT(btn), "name");
    char filepath[512];

    memset(filepath , 0, 512);
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);
    if (music->currentSound != NULL && strcmp(filepath, 
        music->currentSound) == 0 && music->Sound_on == false) {
        mx_unload(music);
    }
}
