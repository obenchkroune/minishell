CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(HEAD) -g3 -fsanitize=address
SRCS	=	$(shell find ./src -type f -name '*.c')
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
