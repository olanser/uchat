# Add new files here

SRC_PATH = src/mx_main_server.c \
	src/mx_create_server.c \
	src/mx_thread.c \
	src/mx_accept_new_connect.c \
	src/mx_new_data_to_socket.c \
	src/mx_check_return_work.c

# Variables

FULL_SRC_PATH = $(SRC_PATH) $(SERVE_PATH)

SRC = $(notdir $(FULL_SRC_PATH))

OUT = $(SRC:%.c=%.o)

OUT_PATH = $(addprefix obj/, $(OUT))

INCF = -I inc \
	-I libs/libmx/inc \
	-I libs/mxinet/inc 

LIBS = libs/libmx.a \
	libs/mxinet.a

INC = inc/defines.h \
	inc/header.h

CFLSGS = -lsqlite3

# Rules

all: test $(OUT_PATH)
	clang -pthread $(CFLSGS) $(OUT_PATH) $(LIBS) -o server -fsanitize=address

install: macos all

obj/%.o: %.c $(INC)
	@clang $(INCF) -c $< -o $@
	@printf "\x1b[32mcompiled:\x1b[34;1m [$@]\x1b[0m\n"

test:
	@cp -p $(FULL_SRC_PATH) .
	@mkdir -p download
	@mkdir -p obj

macos:
	@rm -rf libs/libmx.a 
	@rm -rf libs/mxinet.a 
	@make -sC libs

db:
	@rm -rf database/database.db
	sh database/create_db.sh

uninstall: clean
	@make -sC libs $@
	@rm -rf ./download
	@rm -rf server
	@rm -rf database/database.db
	@printf "\x1b[32mserver:\x1b[34;1m [$@]\x1b[0m\n"

clean:
	@make -sC libs $@
	@rm -rf $(SRC)
	@rm -rf  ./obj

reinstall: uninstall install
