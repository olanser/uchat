TARGET = client

FULL_SRC = src/api/mx_api_send_message.c \
	src/api/mx_api_signin.c \
	src/api/mx_api_signup.c \
	src/init/mx_init.c \
	src/main.c \
	src/init/mx_init_gtk.c \
	src/gtk_cycle/renderer/mx_change_scene.c \
	src/gtk_cycle/renderer/mx_do_iteration.c \
	src/gtk_cycle/renderer/mx_show_window.c \
	src/init/mx_connect_signals.c \
	src/listener/handlers/mx_h_authenticate.c \
	src/listener/handlers/mx_h_create_chat.c \
	src/listener/handlers/mx_h_create_dialog.c \
	src/listener/handlers/mx_h_delete_msg.c \
	src/listener/handlers/mx_h_edit_msg.c \
	src/listener/handlers/mx_h_get_chat_info.c \
	src/listener/handlers/mx_h_get_chat_users.c \
	src/listener/handlers/mx_h_get_file.c \
	src/listener/handlers/mx_h_get_msgs_time.c \
	src/listener/handlers/mx_h_get_user_info.c \
	src/listener/handlers/mx_h_join_chat.c \
	src/listener/handlers/mx_h_leave_chat.c \
	src/listener/handlers/mx_h_read_message.c \
	src/listener/handlers/mx_h_send_file.c \
	src/listener/handlers/mx_h_send_msg.c \
	src/listener/handlers/mx_h_show_users.c \
	src/listener/handlers/mx_h_signin.c \
	src/listener/handlers/mx_h_signup.c \
	src/listener/mx_handle_response.c \
	src/listener/mx_listener.c \
	src/init/mx_connect.c \
	src/api/mx_api_delete_message.c \
	src/api/mx_api_edit_message.c \
	src/api/mx_api_get_chat_users.c \
	src/api/mx_api_get_user_info.c \
	src/api/mx_api_send_file.c \
	src/gtk_cycle/signals/main/mx_btn_send_msg_clicked.c \
	src/gtk_cycle/signals/signin/signin_signal.c \
	src/gtk_cycle/signals/main/main_signals.c \
	src/mx_get_text_textview.c \
	src/api/mx_api_get_chats_info.c \
	src/listener/handlers/mx_h_get_chats_info.c \
	src/gtk_cycle/signals/main/mx_btn_change_chat.c \
	src/api/mx_api_get_chat_info.c \
	src/api/mx_api_get_chat_msgs.c \
	src/mx_get_path_to_sticker.c \
	src/mx_file_reg.c \
	src/api/mx_api_show_users.c \
	src/gtk_cycle/signals/main/mx_expand_focus_in.c \
	src/gtk_cycle/signals/main/mx_expand_focus_out.c \
	src/gtk_cycle/signals/main/mx_expand_changed.c \
	src/gtk_cycle/signals/main/mx_expand_user_click.c \
	src/mx_is_chat_exist.c \
	src/gtk_cycle/mx_go_to_dialog.c \
	src/api/mx_api_create_dialog.c \
	src/gtk_cycle/renderer/mx_scene_cycle.c \
	src/listener/handlers/send_msg/mx_get_msg_widget.c \
	src/gtk_cycle/signals/main/mx_btn_del_msg.c \
	src/mx_get_chat_info.c \
	src/mx_get_msg_by_id.c \
	src/gtk_cycle/signals/main/mx_btn_edit_msg.c \
	src/mx_find_msg.c \
	src/listener/handlers/send_msg/mx_get_msg_from_resp.c \
	src/listener/handlers/send_msg/mx_add_msg_to_box.c \
	src/listener/handlers/send_msg/mx_add_msg_to_list.c \
	src/mx_get_path_to_ava.c \
	src/gtk_cycle/signals/signup/reg_signals.c \
	src/gtk_cycle/signals/signup/mx_btn_signup.c \
	src/gtk_cycle/signals/signin/mx_btn_signin.c \
	src/mx_show_file_dialog.c \
	src/gtk_cycle/signals/main/mx_btn_choose_file.c \
	src/gtk_cycle/signals/main/mx_btn_exit.c \
	src/gtk_cycle/signals/main/mx_btn_show_stickers.c \
	src/init/init_gtk/mx_get_stickers_notebook.c \
	src/gtk_cycle/signals/main/mx_btn_send_sticker.c \
	src/gtk_cycle/signals/main/mx_btn_settings.c \
	src/api/mx_api_get_unique_name_of_file.c \
	src/listener/handlers/mx_h_get_unique_name.c \
	src/file_sender/mx_thread_send_file.c \
	src/api/mx_api_end_send_file.c \
	src/mx_tsend_msg_.c \
	src/mx_send_msg_.c \
	src/listener/handlers/mx_h_who_is_that.c \
	src/api/mx_api_get_file.c \
	src/gtk_cycle/signals/main/mx_btn_get_file.c \

TMP_SRC = $(addprefix tmp/, $(notdir $(FULL_SRC)))

FULL_OBJS = $(addprefix obj/, $(notdir $(FULL_SRC:%.c=%.o)))

A = $(foreach dir, $(dirs), $($(dir):%=)

LIBS = mxinet.a \
	libmx.a \
	mxdraw.a \

INC = -I inc

CHECK_INC = inc/defines_client.h \
	inc/client.h \
	inc/objects.h \


CFG = `pkg-config --cflags gtk+-3.0` 

CFG2 = `pkg-config --libs gtk+-3.0` \
	-pthread \
	-lsqlite3 \
	-rdynamic \

SANITIZE = -fsanitize=address

I = 0

all: premake libs_comile copy $(FULL_OBJS)
	@clang $(FULL_OBJS) $(LIBS) -o $(TARGET) $(CFG) $(CFG2) $(SANITIZE)
	@printf "\x1b[1m\x1b[38;5;10m \x1b[4m=UCHAT=\x1b[0m \x1b[38;5;226mready\x1b[38;5;8m [$I]\x1b[0m\n"

premake:
	@mkdir -p downloads
	@mkdir -p tmp
	@mkdir -p obj
	
libs_comile:
	@make -sC libs
	@mv $(addprefix libs/, $(LIBS)) .
	@cp libs/mxinet/inc/mxinet.h inc
	@cp libs/libmx/inc/libmx.h inc
	@cp libs/mxdraw/inc/mxdraw.h inc

copy:
	@cp -p $(FULL_SRC) ./tmp
	@printf "\x1b[1m\x1b[38;5;26m \x1b[4m=UCHAT=\x1b[0m \x1b[38;5;26mstared\x1b[38;5;8m\x1b[0m\n"

obj/%.o: tmp/%.c $(CHECK_INC)
	@$(eval I :=  $(shell echo "$$(($(I)+1))"))
	@clang -c $< -o $@ $(INC) $(CFG) 
	@printf "\x1b[38;5;118m | $@\x1b[38;18;34m compiled\n"

uninstall: u
	@make -sC libs u
	@rm -rf $(LIBS)
	@rm -rf database/reg
	@rm -rf downloads
u:
	@rm -rf tmp
	@rm -rf obj
