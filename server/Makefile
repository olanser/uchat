# Add new files here

SRC_PATH = src/mx_main_server.c \
	src/mx_create_server.c \
	src/mx_thread.c \
	src/mx_accept_new_connect.c \
	src/mx_new_data_to_socket.c \
	src/mx_compress_array.c \
	src/mx_check_not_work.c \
	src/work_thread/mx_work_thread.c \
	src/function/mx_create_response.c \
	src/work_thread/mx_do_request.c \
	src/work_thread/signup/mx_signup.c \
	src/work_thread/signin/mx_signin.c \
	src/work_thread/send_message/mx_send_message.c \
	src/function/mx_write_socket.c \
	src/function/mx_do_query.c \
	src/function/mx_check_number.c \
	src/function/mx_check_user_in_chat.c \
	src/function/mx_send_response_user.c \
	src/work_thread/edit_message/mx_edit_message.c \
	src/work_thread/signin/mx_get_msg_login.c \
	src/function/mx_callback.c \
	src/work_thread/signup/mx_is_allowed_name.c \
	src/work_thread/signup/mx_check_symbols.c \
	src/work_thread/signup/mx_update_user.c \
	src/work_thread/get_chat_info/mx_get_chat_info.c \
	src/work_thread/get_msgs_time/mx_get_msgs_time.c \
	src/work_thread/show_users/mx_show_users.c \
	src/work_thread/delete_msg/mx_delete_msg.c \
	src/work_thread/send_file/mx_send_file.c \
	src/function/mx_check_id_message_in_user.c \
	src/work_thread/authenticate/mx_authenticate.c \
	src/work_thread/join_chat/mx_join_chat.c \
	src/work_thread/create_chat/mx_create_chat.c \
	src/work_thread/create_dialog/mx_create_dialog.c \
	src/work_thread/leave_chat.c/mx_leave_chat.c \
	src/work_thread/get_user_info/mx_get_user_info.c \
	src/work_thread/get_chat_users/mx_get_chat_users.c \
	src/work_thread/get_chat_users/mx_chat_user_list.c \
	src/work_thread/send_file/mx_create_unique_name.c \

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
	inc/server.h

CFLSGS = -lsqlite3

# Rules

all: test $(OUT_PATH)
	clang -pthread $(CFLSGS) $(OUT_PATH) $(LIBS) -o server

# -fsanitize=address
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
