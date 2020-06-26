SRCS = src/mx_create_sockl.c \
	src/mx_set_sockaddr_any.c \

OBJS = $(SRCS:%.c=%.o)

NAME = mxinet.a

all:
	clang -c $(SRCS)  -I inc
	ar -rc $(NAME) mx_create_sockl.o \
	mx_set_sockaddr_any.o \

uninstall: 
	@rm -rf $(NAME) mx_create_sockl.o \
	mx_set_sockaddr_any.o
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"

clean:
	@rm -rf mx_create_sockl.o \
	mx_set_sockaddr_any.o
	@printf "\x1b[32m$(NAME):\x1b[34;1m [$@]\x1b[0m\n"