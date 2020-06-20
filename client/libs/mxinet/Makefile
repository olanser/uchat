TARGET = mxinet.a

SRC = mx_create_sock.c \
	mx_connect_sock.c \
	mx_create_tcp_lsock.c \
	mx_send_msg.c \
	mx_tsend_msg.c \

INC = -I inc \

CHECKED_INC = inc/mxinet.h

SRC_FULL = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJ_FULL = $(addprefix obj/, $(OBJ))

CFLAGS =  -std=c11 -Werror -Wextra -Wpedantic -Wall

I = 0

all: init $(TARGET)
	@printf "\x1b[1m\x1b[38;5;10m \x1b[4m=MXINET=\x1b[0m \x1b[38;5;226mready\x1b[38;5;8m [$I]\x1b[0m\n"

init:
	@mkdir -p obj

$(TARGET): $(OBJ_FULL)
	@ar rc $(TARGET) $?

obj/%.o: src/%.c
	@$(eval I :=  $(shell echo "$$(($(I)+1))"))
	@clang -c $< $(INC) $(CFLAGS) -o $@
	@printf "\x1b[38;5;34m| $@\x1b[38;18;34m compiled\n"

uninstall u:
	@rm -rf obj $(TARGET)
	@printf "\x1b[1m\x1b[38;5;9m \x1b[4m=MXINET=\x1b[0m \x1b[38;5;214muninstalled\x1b[0m\n"
