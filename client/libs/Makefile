all:
	@make -sC libmx
	@make -sC mxinet
	@mv libmx/libmx.a .
	@mv mxinet/mxinet.a .

unisntall u:
	@make -sC libmx $@
	@make -sC mxinet $@
	@rm -rf libmx.a mxinet.a

# uninstall one lib. usge: u[libname]. example: ulibmx
u%:
	@make -sC $(@:u%=%) u