

OBJD = objs

FULL_PATH_SRC = src/main.c 

SRC_TMP = $(notdir $(FULL_PATH_SRC))

OBJS_TMP = $(SRC_TMP:%.c=%.o)

OBJS_FULL = $(addprefix $(OBJD)/, $(OBJS_TMP))

INC = -I inc \
	-I libmx\inc \


INCLUDE = inc/client_unit.h \

WORKING_TMP = $(notdir $(WORKING))

WORKING_OBJ = $(WORKING_TMP:%.c=%.o)

all: test $(OBJS_FULL)# update only objects from WORKING
	@clang $(OBJS_FULL) $(INC) libmx/libmx.a -o client_unit_test

$(OBJD)/%.o: %.c $(INCLUDE)
	@clang $(INC) -c $< -o $@ 
	@printf "\x1b[32mcompiled:\x1b[34;1m [$@]\x1b[0m\n"

test:
	@make -sC libmx
	@cp -p $(FULL_PATH_SRC) .
	@mkdir -p $(OBJD)

clean:
	@rm -rf $(SRC_TMP)
	@rm -rf $(OBJD)

db:
	@rm -rf database/database.db
	sh database/create_db.sh

install: # Creating all objects
	@cp $(FULL_PATH_SRC) .
	# copied
	@mkdir -p $(OBJD)
	@clang $(SRC_TMP) $(INC) $(CFG) -c
	# compiled
	@mv $(OBJS_TMP) $(OBJD)
	# compiled

	@rm $(SRC_TMP)
	@clang $(OBJS_FULL) $(INC) $(CFG) $(CFG2) -o client_unit_test

# -fsanitize=address
uninstall:
	@make -sC libmx $@
	@rm -rf $(SRC_TMP)
	@rm -rf ./objs
	@rm -rf client_unit_test

clang:
	@clang $(OBJS_FULL) $(INC) $(CFG) $(CFG2) -o client_unit_test