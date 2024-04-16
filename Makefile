CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror $(HEAD) -g3 -fsanitize=address
SRCS	=	$(shell find ./src -type f -name '*.c')
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
