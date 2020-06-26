NAME = libmx.a

INC = inc/libmx.h

HEADTMP = libmx.h

SRC_PATH = ./src/mx_strlen.c \
	./src/mx_strcpy.c \
	./src/mx_strdup.c \
	src/mx_strnew.c \
	src/mx_memcpy.c \
	src/mx_strndup.c \
	src/mx_strjoin.c \
	src/mx_strjoin2.c \
	src/mx_strjoin3.c \
	src/mx_strjoin_len.c \
	src/mx_itoa.c \
	src/mx_str_reverse.c \
	src/mx_push_front.c \
	src/mx_pop_front.c \
	src/mx_create_node.c \
	src/mx_push_back.c \
	src/mx_strdel.c \

SRC = $(notdir $(SRC_PATH))

OUT = $(SRC:%.c=%.o)

OUT1 = $(addprefix obj/, $(OUT))

CFLSGS = #-std=c11 -Wall -Wextra -Wpedantic -Werror 

all: install clean

install:
	@cp $(INC) $(SRC_PATH) .
	@clang $(CFLSGS) -c  $(SRC)
	@mkdir -p obj
	@mv $(OUT) ./obj
	@ar -rc $(NAME) $(OUT1)

uninstall:
	@rm -rf $(OUT1) $(SRC) $(HEADTMP)
	@rm -rf ./obj
	@rm -rf $(NAME)
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"

clean: 
	@rm -rf $(OUT1) $(SRC) $(HEADTMP)
	@rm -rf ./obj
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"

reinstall: uninstall install
