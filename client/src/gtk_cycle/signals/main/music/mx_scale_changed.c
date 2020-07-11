#include "client.h"

gboolean mx_scale_changed (GtkRange *range,
               GtkScrollType scroll,
               gdouble value,
               void *data) {
                printf("value = %f\n", value);
                //FMOD_Channel_SetPosition
                t_fmod_info *music = (t_fmod_info *)data;
                unsigned int position = 0;
                if (value <= 100) {
                    position = (value * music->sound_len)/100;
                    music->possition = position;
                    FMOD_Channel_SetPosition(music->channel, position, FMOD_TIMEUNIT_PCM);
                }
                return FALSE;
               }
