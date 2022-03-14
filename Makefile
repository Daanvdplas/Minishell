NAME		:=	minishell

# Readline -- adjust this for your machine
export RL_LIB	:=	-L/Users/dvan-der/.brew/opt/readline/lib
export RL_INC	:=	-I/Users/dvan-der/.brew/opt/readline/include

# Directories
INCL_DIR	:=	includes
SRCS_DIR	:=	srcs
OBJ_DIR		:=	objs
TEST_DIR	:=	unit-tests
VPATH 		:=	$(subst $(space),:,$(shell find $(SRCS_DIR) -type d))

# Srcs
MAIN		:=	main.c
export SRCS	:=	signals.c \
				exit_error.c \
				tokenizer.c \
				process_char.c \
				process_char_utils.c \
				token_utils.c \
				expander.c \
				parser.c \
				parse_redirects.c \
				resplit_args.c \
				parse_quotes.c \
				parse_words.c \
				redirect_utils.c \
				redirects.c \
				cmd_utils.c \
				executor.c \
				exec_forked_cmd.c \
				init_paths.c \
				ft_putnbr_fd.c \
				built_in.c \
				mini_unset.c \
				mini_echo.c \
				mini_export.c \
				mini_exit.c \
				ft_check_malloc.c \
				ft_free_char_array.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_bzero.c \
				ft_strjoin.c \
				ft_memcpy.c \
				ft_strdup.c \
				ft_strcpy.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_strncmp.c \
				ft_isspace.c \
				ft_isdigit.c \
				ft_strcheck.c \
				ft_strtrim.c \
				ft_strchr.c \
				ft_substr.c \
				ft_itoa.c \
				ft_atoi.c \
				ft_split.c \
				ft_abs.c \
				ft_calloc.c \
				ft_strnstr.c \
				mini_cd.c \
				mini_cd_utils.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_strjoin_free.c \
				here_doc.c \
				mini_export_utils.c \
				unset_export_utils.c \
				ft_isalpha.c \
				ft_isalnum.c
MINI_SRCS	:=	$(SRCS) $(MAIN)
OBJS		:=	$(addprefix $(OBJ_DIR)/, $(MINI_SRCS:.c=.o))

# Config
CC			:=	gcc
ifdef debug
FLAGS		:=	-Wall -Wextra -fsanitize=address -g
else
FLAGS		:=	-Wall -Wextra -Werror -g
endif
LIBS		:=	-lreadline -lhistory

all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(FLAGS) $(LIBS) $(RL_LIB) -o $(NAME)
	@echo success!

$(OBJ_DIR)/%.o: $(notdir %.c)
	@echo "compiling $(notdir $(basename $@))"
	@$(CC) $(FLAGS) -c $< -I$(INCL_DIR) $(RL_INC) -o $@

run: all
	./$(NAME)

drun: all
	lldb $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(TEST_DIR) clean

fclean:	clean
	@rm -f $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# used for unit tests
export double_var	:=	$$env_var
export env_var		:=	blabla
export a9			:=	jup
export ls			:=	ls -l
export ls2			:=	ls    -l
test: $(OBJ_DIR)
	@$(MAKE) -C $(TEST_DIR) test

dtest: $(OBJ_DIR)
	@$(MAKE) -C $(TEST_DIR) clean
	@$(MAKE) -C $(TEST_DIR) dtest

re:	fclean all

.PHONY:	all clean fclean re