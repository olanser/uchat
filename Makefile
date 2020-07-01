all:
	@make -sC server
	@make -sC client

uninstall:
	@make -sC server $@
	@make -sC client $@
	@make -sC unit_test/client $@

clean:
	@make -sC server $@
	@make -sC client $@
	@make -sC unit_test/client $@
