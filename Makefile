NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(HEAD)

OBJS_DIR	=	./obj
SRCS_DIR	=	./src

SRC_FILES	=	utils/ft_get_exit_status.c builtins/cd.c builtins/echo.c builtins/env.c
				builtins/exit.c builtins/export.c builtins/history.c builtins/pwd.c
				builtins/unset.c env/append_env.c env/env_utils.c env/get_env.c
				env/parse_env.c env/set_env.c exec/exec.c exec/exec_builtins.c
				exec/exec_simple_cmd.c exec/redirect.c exec/signals.c exec/terminal.c
				expantion/expand.c expantion/expand_argv.c expantion/wildcard.c
				lexer/get_next_token.c lexer/peek.c lib/free_tab.c lib/ft_isspace.c
				lib/ft_strreplace.c lib/ft_tabsize.c main.c parser/args.c
				parser/get_redir_fd.c parser/join_args.c parser/parse_ast.c
				parser/parse_cmd.c parser/parse_input.c parser/parser_utils.c
				parser/replace_vars.c utils/append_input.c utils/cleanup_shell.c
				utils/display_prompt.c utils/free_tree.c utils/get_display_line.c
				utils/init_shell.c utils/is_empty.c utils/panic.c utils/print_env.c
				utils/set_pwd.c utils/set_status.c utils/syntax_error.c
				utils/get_executable.c
HEAD		=	-I includes -I ~/.local/include
SRCS		=	$(addprefix $(SRCS_DIR)/, $(SRC_FILES))
CLIBS		=	-Llibft -lft -L ~/.local/lib -lreadline -lcurses
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

RM			=	rm -rf
MKDIR		=	mkdir -p

ifeq ($(DEBUG), 1)
	CFLAGS	+=	-g3 -fsanitize=address
endif

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) Makefile
	make -C libft
	$(MKDIR) $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CLIBS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS_DIR)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: clean fclean all re
