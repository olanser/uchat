#include "client.h"
#include "defines_client.h"

static void initialise(FMOD_SYSTEM **fmodsystem, bool *possible, 
                       FMOD_CHANNEL **channel) {
    FMOD_RESULT result;

    //create the sound system. If fails, sound is set to impossible
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
