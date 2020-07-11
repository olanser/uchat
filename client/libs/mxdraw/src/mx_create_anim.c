/* 
* author vbalachevs
* Creating animation object
*/
#include "mxdraw.h"

t_anim* mx_create_anim(const char** imgs, int count_sprites, int duration) {
    t_anim* anim = malloc(sizeof(t_anim));

    anim->count_sprites = count_sprites;
    anim->current_sprite = 0;
    anim->anim_time = duration / anim->count_sprites;
    anim->images = malloc(sizeof(GtkImage*) * anim->count_sprites);
    for (int i = 0; i < anim->count_sprites; i++)
        anim->images[i] = gtk_image_new_from_file(imgs[i]);
    return anim;
}
