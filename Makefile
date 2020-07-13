name_server = chat_server
name_client = uchat

all: lib server_ client_

$(name_server): lib server_

server_: server/inc/openssl
	@make -sC server
	@cp server/chat_server .

$(name_client): lib client_

client_: client/inc/openssl
	@make -sC client
	@cp client/uchat .

client/inc/openssl: libfile/openssl/openssl
	@cp -R libfile/openssl/openssl client/inc
	@cp libfile/libcrypto.dylib libfile/libssl.dylib client/libs

server/inc/openssl: libfile/openssl/openssl
	@cp -R libfile/openssl/openssl server/inc
	@cp libfile/libcrypto.dylib libfile/libssl.dylib server/libs

lib:
	@make -sC libfile

uninstall: clean
	@make -sC server $@
	@make -sC client $@
	@make -sC libfile $@
	@rm -rf $(name_client) $(name_server)

clean:
	@make -sC server $@
	@make -sC client $@

reinstall: uninstall all
