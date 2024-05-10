OBJS_DIR	=	./obj
SRCS_DIR	=	./src

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(HEAD)
SRC_FILES	=	parser/join_args.c parser/parser_utils.c parser/parse_cmd.c \
				parser/replace_vars.c parser/args.c parser/parse_input.c \
				parser/get_redir_fd.c parser/parse_pipe.c expantion/expand_argv.c \
				expantion/expand.c expantion/expand_redir.c env/env_utils.c \
				env/set_env.c env/parse_env.c env/get_env.c utils/init_shell.c \
				utils/cleanup_shell.c utils/display_prompt.c utils/is_empty.c \
				utils/free_tree.c utils/set_pwd.c utils/get_display_line.c \
				utils/append_input.c utils/set_status.c utils/syntax_error.c \
				utils/panic.c exec/exec_builtins.c exec/exec.c exec/redirect.c \
				exec/terminal.c exec/signals.c exec/exec_simple_cmd.c builtins/echo.c \
				builtins/unset.c builtins/exit.c builtins/export.c builtins/env.c \
				builtins/history.c builtins/cd.c builtins/pwd.c lexer/peek.c \
				lexer/get_next_token.c lib/ft_isspace.c lib/ft_strreplace.c \
				lib/free_tab.c lib/ft_tabsize.c expantion/wildcard.c main.c
SRCS		=	$(addprefix ./src/, $(SRC_FILES))
HEAD		=	-I includes -I ~/.local/include
CLIBS		=	-Llibft -lft -L ~/.local/lib -lreadline -lcurses
OBJS		=	$(patsubst ./src/%.c, ./obj/%.o, $(SRCS))
NAME		=	minishell
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
