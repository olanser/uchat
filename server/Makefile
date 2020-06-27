# Add new files here

SRC_PATH = src/server.c \
	src/mx_pop_index.c \
	src/mx_create_node.c \
	src/mx_push_top.c \
	src/serve/mx_read_socket.c \
	src/serve/mx_handle_input.c \
	src/serve/mx_handle_out.c \
	src/serve/sendmessage/mx_send_message.c \
	src/serve/sendmessage/mx_check_message.c \
	src/serve/sendmessage/mx_check_user_in_char.c \
	src/serve/sendmessage/mx_create_response.c \
	src/serve/sendmessage/mx_check_number.c \
	src/serve/sendmessage/mx_create_signal_new_message.c \
	src/serve/editmessage/mx_editmessage.c \
	src/serve/delete_msg/mx_delete_msg.c \
	src/serve/get_msgs_time/mx_get_msgs_time.c \
	src/serve/get_user_info/mx_get_user_info.c \
	src/serve/signup/mx_check_symbols.c \
	src/serve/signup/mx_is_allowed_name.c \
	src/serve/signup/mx_signup.c \
	src/serve/mx_do_query.c \
	src/serve/signup/mx_update_user.c \
	src/serve/signin/mx_signin.c \
	src/serve/signin/mx_get_msg_login.c \
	src/serve/show_users/mx_show_users.c \
	src/serve/get_chat_info/mx_get_msg_chat.c \
	src/serve/get_chat_info/mx_get_chat_info.c \
	src/serve/mx_free_tuser.c \
	src/serve/mx_upd_pr_data.c \
	src/serve/pthread_updates/mx_create_pthread_updates.c \
	src/serve/pthread_updates/mx_callback_updates.c \
	src/serve/get_chat_users/mx_get_chat_users.c \
	src/serve/get_chat_users/mx_chat_user_list.c \
	src/serve/authenticate/mx_authenticate.c \
	src/serve/join_chat/mx_get_msg_response_10.c \
	src/serve/join_chat/mx_join_chat.c \
	src/serve/create_chat/mx_create_chat.c \
	src/serve/create_dialog/mx_create_dialog.c \
	src/serve/leave_chat/mx_leave_chat.c \
	src/serve/mx_send_file/mx_send_file.c

SERVE_PATH = src/serve/serve.c \

# Variables

FULL_SRC_PATH = $(SRC_PATH) $(SERVE_PATH)

SRC = $(notdir $(FULL_SRC_PATH))

OUT = $(SRC:%.c=%.o)

OUT_PATH = $(addprefix obj/, $(OUT))
INCF = -I inc \
	-I libs/mxinet/inc/ \
	-I libs/libmx/inc \

LIBS = libs/mxinet.a \
	libs/libmx.a \

INC = inc/defines.h \
	inc/header.h \

CFLSGS = -lsqlite3

# Rules

all: test $(OUT_PATH)
	clang -pthread $(CFLSGS) $(OUT_PATH) $(LIBS) -o server

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
	@rm -rf ./download
	@rm -rf server
	@rm -rf database/database.db
	@make -sC libs $@

clean:
	@rm -rf $(SRC)
	@rm -rf  ./obj

reinstall: uninstall install
