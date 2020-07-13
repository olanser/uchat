#include "client.h"
#include "defines_client.h"

static void initialise(FMOD_SYSTEM **fmodsystem, bool *possible, 
                       FMOD_CHANNEL **channel) {
    FMOD_RESULT result;

    result = FMOD_System_Create(fmodsystem);
    if (result != FMOD_OK) 
        *possible = false;
    //if initialise the sound system. If fails, sound is set to impossible
    if (*possible) {
        result = FMOD_System_Init(*fmodsystem,2, FMOD_INIT_NORMAL, 0);
    }
    if (result != FMOD_OK) 
        *possible = false;
    if (*possible) {
        FMOD_Channel_SetVolume(*channel,0.0f);
    }
}

t_fmod_info *mx_init_music() {
    t_fmod_info *music = (t_fmod_info *)malloc(sizeof(t_fmod_info));

    music->channel = NULL;
    music->currentSound = NULL;
    music->fmodsystem =  NULL;
    music->pause = false;
    music->possible = true;
    music->possition = 0;
    music->sound = NULL;
    music->Sound_on = true;
    music->sound_to_pay = NULL;
    music->sound_len = 0;

    initialise(&(music->fmodsystem), &(music->possible), &(music->channel));
    return music;
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
        FMOD_Channel_GetPosition(music->channel, &position,FMOD_TIMEUNIT_PCM);
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
        mx_unload(music);
    return 0;
}
