all:
	@make -sC libmx
	@make -sC mxinet
	@make -sC mxdraw
	@mv libmx/libmx.a .
	@mv mxinet/mxinet.a .
	@mv mxdraw/mxdraw.a .

unisntall u:
	@make -sC libmx $@
	@make -sC mxinet $@
	@make -sC mxdraw $@
	@rm -rf libmx.a mxinet.a mxdraw.a

# uninstall one lib. usge: u[libname]. example: ulibmx
u%:
	@make -sC $(@:u%=%) u