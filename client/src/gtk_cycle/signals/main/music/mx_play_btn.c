#include "client.h"
#include "defines_client.h"

void initialise(FMOD_SYSTEM **fmodsystem, bool *possible, FMOD_CHANNEL **channel) {
    FMOD_RESULT result;    

    //create the sound system. If fails, sound is set to impossible
    result = FMOD_System_Create(fmodsystem);
    if (result != FMOD_OK) 
        *possible = false;
    //if initialise the sound system. If fails, sound is set to impossible
    if (*possible) {
        result = FMOD_System_Init(*fmodsystem,2, FMOD_INIT_NORMAL, 0);
        printf("initial system\n");
    }
    if (result != FMOD_OK) 
        *possible = false;
    //sets initial sound volume (mute)
    if (*possible) {
        printf("initial chanel\n");
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



//loads a soundfile
void load (t_fmod_info *music) {
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

void *mx_music_scrol(void *data) {
    t_fmod_info *music = (t_fmod_info *)data;
    unsigned int position = 0;
    int value = 0;


    while(1) {
        FMOD_Channel_GetPosition(music->channel, &position, FMOD_TIMEUNIT_PCM);
        value = (position * 100)/music->sound_len;
        gtk_range_set_value(GTK_RANGE(music->scale), value);
    }
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


// FMOD_RESULT FMOD_Sound_GetLength(
//   FMOD_SOUND *sound,
//   unsigned int *length,
//   FMOD_TIMEUNIT lengthtype
// );


void togglePause (FMOD_CHANNEL *channel) {
    FMOD_BOOL p;
    FMOD_Channel_GetPaused(channel,&p);
    FMOD_Channel_SetPaused(channel,!p);
}

void unload (t_fmod_info *music) {
    FMOD_RESULT result;
    if (music->possible) {
        result = FMOD_Sound_Release(music->sound);
        music->Sound_on = true;
        music->pause = false;
        music->sound = NULL;
        music->currentSound = NULL;
        mx_strdel(&(music->sound_to_pay));
        printf("delte_song\n");
    }
}
static bool check_song(char *filename, char *currentname) {
    if (currentname != NULL && strcmp(currentname, filename) != 0)
        return true;
    return false;
}


void toggleSound (t_fmod_info *mus) {
    //*Sound_on  = !(*Sound_on);
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

    // if (*Sound_on == false) { 
    //     unload(*possible, sound, music);
    //     *sound = NULL;
    // }
}



void mx_play_btn(GtkButton *btn, void*data) {
    printf("\n\n********CLECKEd********\n\n");
    t_fmod_info *music = (t_fmod_info *)data;
    char *name = g_object_get_data(G_OBJECT(btn), "name");
    GtkWidget *scale = g_object_get_data(G_OBJECT(btn), "scale");
    music->scale = scale;
    char filepath[512];

    printf("File Name: %s\n", name);
    memset(filepath , 0, 512);
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);
    
    //gtk_range_set_value(GTK_RANGE(scale), 80.0);
    if (music->sound_to_pay == NULL) {
        music->sound_to_pay = strdup(filepath);
        //printf("File Name1: %s\n", music->sound_to_pay);
    }
    else {
        if (check_song(filepath, music->currentSound)) {
            printf("********start unload********\n");
            printf("ti play: %s\n", music->sound_to_pay);
            printf("Curent: %s\n", music->currentSound);
            unload(music);
            music->sound_to_pay = strdup(filepath);

        }
    }
    printf("ti play: %s\n", music->sound_to_pay);
    printf("Curent: %s\n", music->currentSound);
    toggleSound(music);
}

void mx_stop_btn(GtkButton *btn, void*data) {
    printf("\n\n********CLECKEd STOP********\n\n");
    t_fmod_info *music = (t_fmod_info *)data;
    char *name = g_object_get_data(G_OBJECT(btn), "name");
    char filepath[512];

    printf("File Name: %s\n", name);
    printf("Curent: %s\n", music->currentSound);
    memset(filepath , 0, 512);
    sprintf(filepath, "%s%s", MX_DIR_DOWNLOAD, name);

    if (strcmp(filepath, music->currentSound) == 0)
        unload(music);
}
