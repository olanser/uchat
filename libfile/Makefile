files = openssl/lib/libcrypto.3.dylib \
	openssl/lib/libcrypto.a \
	openssl/lib/libcrypto.pc \
	openssl/lib/libcrypto.dylib \
	openssl/lib/libssl.3.dylib \
	openssl/lib/libssl.a \
	openssl/lib/libssl.dylib \
	openssl/lib/libssl.pc \

files2 = $(notdir $(files))

all:
	@cp $(files) .
	@install_name_tool -id $(CURDIR)/libssl.3.dylib libssl.dylib
	@install_name_tool -change /Users/solianovsk/Desktop/finish/libfile/openssl/lib/libcrypto.3.dylib $(CURDIR)/libcrypto.3.dylib libssl.dylib
	@install_name_tool -id $(CURDIR)/libcrypto.3.dylib libcrypto.dylib

uninstall:
	@rm -rf $(files2)
 