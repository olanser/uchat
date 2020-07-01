LIB_FILES = libmx/libmx.a \
	mxinet/mxinet.a

LIB_FILES_TMP = $(notdir $(LIB_FILES))

all: MAKE_LIB $(LIB_FILES_TMP)

MAKE_LIB:
	@make -sC libmx
	@make -sC mxinet

%.a: libmx/%.a
	@cp -p $< .
	@printf "\x1b[32mCP:\x1b[34;1m [$@]\x1b[0m\n"

%.a: mxinet/%.a
	@cp -p $< .
	@printf "\x1b[32mCP:\x1b[34;1m [$@]\x1b[0m\n"

uninstall: clean
	@make -sC libmx $@
	@make -sC mxinet $@
	@rm -rf $(LIB_FILES_TMP)
	@printf "\x1b[32mlibs:\x1b[34;1m [$@]\x1b[0m\n"

clean:
	@make -sC libmx $@
	@make -sC mxinet $@
	@printf "\x1b[32mlibs:\x1b[34;1m [$@]\x1b[0m\n"
