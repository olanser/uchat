TARGET = libmx.a

SRC = mx_add_strarr.c \
	mx_arrstr_to_str.c \
	mx_binary_search.c \
	mx_bubble_sort.c \
	mx_count_substr.c \
	mx_count_words.c \
	mx_create_node.c \
	mx_del_extra_spaces.c \
	mx_del_strarr.c \
	mx_dupstrarr.c \
	mx_file_to_str.c \
	mx_foreach.c \
	mx_get_char_index.c \
	mx_get_substr_index.c \
	mx_get_user_home.c \
	mx_get_user_name.c \
	mx_getchar.c \
	mx_hex_to_nbr.c \
	mx_is_str_starts.c \
	mx_isspace.c \
	mx_itoa.c \
	mx_list_size.c \
	mx_memccpy.c \
	mx_memchr.c \
	mx_memcmp.c \
	mx_memcpy.c \
	mx_memmem.c \
	mx_memmove.c \
	mx_memrchr.c \
	mx_memset.c \
	mx_nbr_to_hex.c \
	mx_pop_back.c \
	mx_pop_front.c \
	mx_pop_list.c \
	mx_pow.c \
	mx_print_strarr.c \
	mx_print_unicode.c \
	mx_printchar.c \
	mx_printerr.c \
	mx_printint.c \
	mx_printstr.c \
	mx_push_back.c \
	mx_push_front.c \
	mx_quicksort.c \
	mx_read_line.c \
	mx_realloc.c \
	mx_replace_substr.c \
	mx_sort_list.c \
	mx_sqrt.c \
	mx_str_reverse.c \
	mx_strcat.c \
	mx_strcmp.c \
	mx_strcmp2.c \
	mx_strcpy.c \
	mx_strdel.c \
	mx_strdup.c \
	mx_strjoin.c \
	mx_strjoin2.c \
	mx_strjoin3.c \
	mx_strlen.c \
	mx_strncmp.c \
	mx_strncpy.c \
	mx_strndup.c \
	mx_strnew.c \
	mx_strsplit.c \
	mx_strstr.c \
	mx_strtrim.c \
	mx_swap_char.c \

INC = -I inc \

CHECKED_INC = inc/libmx.h

SRC_FULL = $(addprefix src/, $(SRC))

OBJ = $(SRC:%.c=%.o)

OBJ_FULL = $(addprefix obj/, $(OBJ))

CFLAGS = 

I = 0

all: init $(TARGET)
	@printf "\x1b[1m\x1b[38;5;10m \x1b[4m=LIBMX=\x1b[0m \x1b[38;5;226mready\x1b[38;5;8m [$I]\x1b[0m\n"

init:
	@mkdir -p obj

$(TARGET): $(OBJ_FULL)
	@ar rc $(TARGET) $?

obj/%.o: src/%.c
	@$(eval I :=  $(shell echo "$$(($(I)+1))"))
	@clang -c $< $(INC) $(CFLAGS) -o $@
	@printf "\x1b[38;5;34m| $@\x1b[38;18;34m compiled\n"
	

uninstall u:
	@rm -rf obj $(TARGET)
	@printf "\x1b[1m\x1b[38;5;9m \x1b[4m=LIBMX=\x1b[0m \x1b[38;5;214muninstalled\x1b[0m\n"
