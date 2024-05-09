CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror $(HEAD) -fsanitize=address -ggdb
SRCS	=	./src/parser/join_args.c ./src/parser/parser_utils.c ./src/parser/parse_cmd.c \
			./src/parser/replace_vars.c ./src/parser/args.c ./src/parser/parse_input.c \
			./src/parser/get_redir_fd.c ./src/parser/parse_pipe.c ./src/expantion/expand_argv.c \
			./src/expantion/expand.c ./src/expantion/expand_redir.c ./src/env/set_env.c \
			./src/env/parse_env.c ./src/env/get_env.c ./src/utils/init_shell.c \
			./src/utils/cleanup_shell.c ./src/utils/display_prompt.c ./src/utils/is_empty.c \
			./src/utils/free_tree.c ./src/utils/get_display_line.c ./src/utils/append_input.c \
			./src/utils/syntax_error.c ./src/utils/panic.c ./src/exec/exec_builtins.c \
			./src/exec/exec.c ./src/exec/redirect.c ./src/exec/terminal.c ./src/exec/signals.c \
			./src/exec/exec_simple_cmd.c ./src/builtins/echo.c ./src/builtins/unset.c \
			./src/builtins/cd_utils.c ./src/builtins/exit.c ./src/builtins/export.c \
			./src/builtins/env.c ./src/builtins/history.c ./src/builtins/cd.c \
			./src/builtins/pwd.c ./src/lexer/peek.c ./src/lexer/get_next_token.c \
			./src/lib/ft_isspace.c ./src/lib/ft_strreplace.c ./src/lib/free_tab.c \
			./src/lib/ft_tabsize.c ./src/main.c
HEAD	=	-I includes -I ~/.local/include
CLIBS	=	-Llibft -lft -L ~/.local/lib -lreadline -lcurses
OBJS	=	$(SRCS:.c=.o)
NAME	=	minishell
AR		=	ar rcs
RM		=	rm -f

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(CLIBS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: clean fclean all re
