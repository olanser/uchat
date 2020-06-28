all:
	@make -sC server $@

uninstall:
	printf "1\n"
	@make -sC server $@
	printf "2\n"
	@make -sC client $@
	printf "3\n"
	@make -sC unit_test/client $@
	printf "4\n"

clean:
	@make -sC server $@
	@make -sC client $@
	@make -sC unit_test/client $@
