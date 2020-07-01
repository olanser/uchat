SRCS = src/mx_create_sockl.c \
	src/mx_set_sockaddr_any.c \

OBJS = $(addprefix obj/, $(notdir $(SRCS:%.c=%.o)))

NAME = mxinet.a

CFLSGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install

install: $(NAME)

$(NAME): obj $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@printf "\x1b[32mcompiled:\x1b[34;1m [$(NAME)]\x1b[0m\n"

obj/%.o: src/%.c
	@clang $(CFLSGS) -c $< -o $@ -I inc
	@printf "\x1b[32mcompiled:\x1b[34;1m [$@]\x1b[0m\n"

obj:
	@mkdir -p obj

uninstall: clean
	@rm -rf $(NAME)
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"

clean:
	@rm -rf obj
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"