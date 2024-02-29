CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	main.c
HEAD = includes
LFLAGS = -Llibft -lft -lreadline
OBJS = $(SRCS:.c=.o)
NAME = minishell
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEAD) $(LFLAGS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: clean fclean all re