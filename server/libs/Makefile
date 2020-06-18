LIB_FILES = libmx/libmx.a \
	mxinet/mxinet.a

LIB_FILES_TMP = $(notdir $(LIB_FILES))

all:
	make -sC libmx
	make -sC mxinet
	cp $(LIB_FILES) .

uninstall:
	make -sC libmx uninstall
	make -sC mxinet uninstall
	rm $(LIB_FILES_TMP)
