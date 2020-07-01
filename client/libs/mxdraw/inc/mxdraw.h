#ifndef MXDRAW_H
#define MXDRAW_H

#include <gtk/gtk.h>

typedef struct s_anim {
    int count_sprites;
    int anim_time; // 1 - 33ms, 2 - 66ms change sprite
    int anim_stage; // for animation
    int current_sprite; // current sprite
    GtkWidget **images; // massieve of sprites
} t_anim;

typedef struct s_vec2 {
    float x;
    float y;
} t_vec2;

typedef struct s_movable {
    t_vec2 pos; // current position
    t_vec2 mov; // moving vector
} t_movable;

typedef struct s_dr_obj { // drawable object
    t_movable movable;
    t_anim *anim;
} t_dr_obj;

// Functions

void mx_draw_anim(int cycle, t_anim *anim);

t_anim* mx_create_anim(
    const char** imgs,
    int count_sprites,
    int duration
);

t_movable mx_crerate_movable(t_vec2 pos, t_vec2 mov);

t_dr_obj* mx_create_drobject(
    t_movable movable,
    const char** imgs,
    int count_sprites,
    int duration
);
void mx_put_obj(GtkLayout* layout, t_dr_obj *obj);
void mx_move_obj(t_dr_obj *obj);
void mx_paly_object(GtkLayout *layout, t_dr_obj *obj, int cycle);
#endif