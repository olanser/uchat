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

TMP_SRC = $(addprefix tmp/, $(notdir $(FULL_SRC)))

FULL_OBJS = $(addprefix obj/, $(notdir $(FULL_SRC:%.c=%.o)))

LIBS = mxinet.a \
	libmx.a \

INC = -I inc

CHECK_INC = inc/defines.h

CFG = `pkg-config --cflags gtk+-3.0` 

CFG2 = `pkg-config --libs gtk+-3.0` \
	-pthread \
	-lsqlite3 \
	-rdynamic \

all: premake libs_comile copy $(FULL_OBJS)
	@clang $(FULL_OBJS) $(LIBS) -o $(TARGET) $(CFG) $(CFG2) 
	
premake:
	@mkdir -p tmp
	@mkdir -p obj

libs_comile:
	@make -sC libs
	@mv $(addprefix libs/, $(LIBS)) .
	@cp libs/mxinet/inc/mxinet.h inc
	@cp libs/libmx/inc/libmx.h inc

copy:
	cp -p $(FULL_SRC) ./tmp

obj/%.o: tmp/%.c $(CHECK_INC)
	clang -c $< -o $@ $(INC) $(CFG)

uninstall: u
	@make -sC libs u
	@rm $(LIBS)

u:
	rm -rf tmp
	rm -rf obj
