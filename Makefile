all:
	@cp -R libfile/openssl/openssl client/inc
	@cp -R libfile/openssl/lib client
	@cp -R libfile/openssl/openssl server/inc
	@cp -R libfile/openssl/lib server
	@make -sC server
	@make -sC client

uninstall: uninstall_openssl
	@make -sC server $@
	@make -sC client $@
	@make -sC unit_test/client $@

clean: uninstall_openssl
	@make -sC server $@
	@make -sC client $@
	@make -sC unit_test/client $@

uninstall_openssl:
	@rm -rf server/lib
	@rm -rf client/lib
	@rm -rf server/inc/openssl
	@rm -rf client/inc/openssl