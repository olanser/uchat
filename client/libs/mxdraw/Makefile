TARGET = mxdraw.a

SRC = mx_create_anim.c \
	mx_draw_anim.c \
	mx_crerate_movable.c \
	mx_create_drobject.c \
	mx_put_obj.c \
	mx_move_obj.c \
	mx_play_object.c \

INC = -I inc \

CHECKED_INC = inc/mxdraw.h

SRC_FULL = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJ_FULL = $(addprefix obj/, $(OBJ))

CFLAGS = 

CFG = `pkg-config --cflags gtk+-3.0` 

CFG2 = `pkg-config --libs gtk+-3.0` \
	-pthread \
	-lsqlite3 \
	-rdynamic \

I = 0

all: init $(TARGET)
	@printf "\x1b[1m\x1b[38;5;10m \x1b[4m=MXDRAW=\x1b[0m \x1b[38;5;226mready\x1b[38;5;8m [$I]\x1b[0m\n"

init:
	@mkdir -p obj

$(TARGET): $(OBJ_FULL)
	@ar rc $(TARGET) $?

obj/%.o: src/%.c
	@$(eval I :=  $(shell echo "$$(($(I)+1))"))
	@clang -c $< $(INC) $(CFLAGS) -o $@ $(CFG)
	@printf "\x1b[38;5;34m| $@\x1b[38;18;34m compiled\n"
	

uninstall u:
	@rm -rf obj $(TARGET)
	@printf "\x1b[1m\x1b[38;5;9m \x1b[4m=MXDRAW=\x1b[0m \x1b[38;5;214muninstalled\x1b[0m\n"
