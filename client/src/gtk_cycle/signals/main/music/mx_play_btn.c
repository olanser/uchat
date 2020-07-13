#include "client.h"
#include "defines_client.h"

static void play(t_fmod_info *music) {
    FMOD_RESULT result;
    if (music->possible && music->Sound_on) {
        FMOD_Sound_GetLength(music->sound, &(music->sound_len),
                             FMOD_TIMEUNIT_PCM);
        result = FMOD_System_PlaySound(music->fmodsystem,FMOD_CHANNEL_FREE, 
                                      music->sound, music->pause,
                                      &(music->channel));
        FMOD_Channel_SetMode(music->channel,FMOD_LOOP_NORMAL);
        pthread_create(&(music->thread), 0, mx_music_scrol, music);
    }
}



static void togglePause(FMOD_CHANNEL *channel) {
    FMOD_BOOL p;
    FMOD_Channel_GetPaused(channel,&p);
    FMOD_Channel_SetPaused(channel,!p);
}


static bool check_song(char *filename, char *currentname) {
    if (currentname != NULL && strcmp(currentname, filename) != 0)
        return true;
    return false;
}


static void toggleSound(t_fmod_info *mus) {
    if (mus->Sound_on == true) { 
        if (mus->pause == false) {
            mx_load(mus);
            play(mus);
            mus->pause = true;
            mus->Sound_on = !(mus->Sound_on);
        }
    }
    else {
        if (mus->pause == true)
            togglePause(mus->channel);
        }
}

void mx_play_btn(GtkButton *btn, void*data) {
    t_fmod_info *music = (t_fmod_info *)data;
    char *name = g_object_get_data(G_OBJECT(btn), "name");
    GtkWidget *scale = g_object_get_data(G_OBJECT(btn), "scale");
    char filepath[512];

    mx_change_btn(btn);
    memset(filepath , 0, 512);
    music->scale = scale;
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);
    if (music->sound_to_pay == NULL)
        music->sound_to_pay = strdup(filepath);
    else {
        if (check_song(filepath, music->currentSound)) {
            mx_unload(music);
            music->scale = scale;
            music->sound_to_pay = strdup(filepath);
        }
    }
    toggleSound(music);
}
