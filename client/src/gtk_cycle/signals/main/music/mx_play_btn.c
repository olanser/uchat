#include "client.h"
#include "defines_client.h"


void unload(t_fmod_info *music) {
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


//loads a soundfile
void load(t_fmod_info *music) {
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

static gboolean foo(void* data) {
    GtkWidget *scale = (GtkWidget*)((void**)data)[0];
    double value = (double)(long long)((void**)data)[1];
    gtk_range_set_value(GTK_RANGE(scale), value);

    free(data);
    return 0;
}

static void build_data(t_fmod_info *music, double value) {
    void **data = malloc(sizeof(void*) * 2);

    data[0] = music->scale;
    data[1] = (void*)(long long)value;
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, foo, data, 0);
}

void *mx_music_scrol(void *data) {
    t_fmod_info *music = (t_fmod_info *)data;
    unsigned int position = 0;
    double value = 0;
    int buf = 0;

    while(value < 99 && music->Sound_on == false) {
        FMOD_Channel_GetPosition(music->channel, &position, FMOD_TIMEUNIT_PCM);
        value = (double)((double)position * 100)/(double)music->sound_len;
        if (value <= 100 && value >= 0 && music->scale != NULL) {
            if (buf < (int) value + 1) {
                buf = (int) value + 1;
                build_data(music, value);
            }
            else
                sleep(1);
        }
    }
    if (music->Sound_on == false)
        unload(music);
    return 0;
}

void play (t_fmod_info *music) {
    FMOD_RESULT result;
    if (music->possible && music->Sound_on) {
        FMOD_Sound_GetLength(music->sound, &(music->sound_len),
                             FMOD_TIMEUNIT_PCM);
        result = FMOD_System_PlaySound(music->fmodsystem,FMOD_CHANNEL_FREE, 
                                music->sound, music->pause, &(music->channel));
        FMOD_Channel_SetMode(music->channel,FMOD_LOOP_NORMAL);
        pthread_create(&(music->thread), 0, mx_music_scrol, music);
    }
}



void togglePause (FMOD_CHANNEL *channel) {
    FMOD_BOOL p;
    FMOD_Channel_GetPaused(channel,&p);
    FMOD_Channel_SetPaused(channel,!p);
}


static bool check_song(char *filename, char *currentname) {
    if (currentname != NULL && strcmp(currentname, filename) != 0)
        return true;
    return false;
}


void toggleSound(t_fmod_info *mus) {
    if (mus->Sound_on == true) { 
        if (mus->pause == false) {
            load(mus);
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

    memset(filepath , 0, 512);
    music->scale = scale;
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);
    if (music->sound_to_pay == NULL)
        music->sound_to_pay = strdup(filepath);
    else {
        if (check_song(filepath, music->currentSound)) {
            unload(music);
            music->scale = scale;
            music->sound_to_pay = strdup(filepath);
        }
    }
    toggleSound(music);
}

void mx_stop_btn(GtkButton *btn, void*data) {
    t_fmod_info *music = (t_fmod_info *)data;
    char *name = g_object_get_data(G_OBJECT(btn), "name");
    char filepath[512];

    memset(filepath , 0, 512);
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);

    if (music->currentSound != NULL && strcmp(filepath, 
        music->currentSound) == 0 && music->Sound_on == false) {
        unload(music);
    }
}
