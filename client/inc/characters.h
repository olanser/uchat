#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "mxdraw.h"

#define MX_PACMAN_ANIM_DUR 8 /* iterations */
#define MX_PACMAN_COUNT_SP 2
#define MX_PAC_SP1 "res/anim/pacman/pacman1.tiff"
#define MX_PAC_SP2 "res/anim/pacman/pacman2.tiff"

typedef struct s_pacman t_pacman;

typedef struct s_characters {
    t_pacman *pacman;
} t_characters;

typedef struct s_pacman {
    t_dr_obj *draw_obj;
} t_pacman;

#endif
