#ifndef DEFINES_H
#define DEFINES_H

#define MX_PATH_TO_TEMPLATE "templates/resizable8.xml" //resizable6 - has expander; resizable2 - without;
#define MX_TEMPLATE_SHITS "templates/notebook_chats.xml"
#define MX_COUNT_API 17
#define MX_FILE_REG "database/reg"
#define SIGNIN_CSS_STYLE "templates/signin_theme.css"
#define MX_MAX_SICKER 0

typedef enum {
    MX_SCENE_SIGNUP,
    MX_SCENE_SIGNIN,
    MX_SCENE_MAIN_CHAT
} t_num_scenes;

#endif
