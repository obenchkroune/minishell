CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEAD)
SRCS	=	src/lexer/token_utils.c src/lexer/tokenize.c src/lexer/has_valid_syntax.c \
			src/lexer/free_tokens.c src/main.c
HEAD	=	includes
CLIBS	=	-Llibft -lft -lreadline
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