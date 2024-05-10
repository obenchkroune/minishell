OBJS_DIR	=	./obj
SRCS_DIR	=	./src

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(HEAD)
SRCS		=	$(shell find ./src -type f -name "*.c")
HEAD		=	-I includes -I ~/.local/include
CLIBS		=	-Llibft -lft -L ~/.local/lib -lreadline -lcurses
OBJS		=	$(patsubst ./src/%.c, ./obj/%.o, $(SRCS))
NAME		=	minishell
AR			=	ar rcs
RM			=	rm -f
MKDIR		=	mkdir -p

ifeq ($(DEBUG), 1)
	CFLAGS	+=	-g3 -fsanitize=address
endif

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(MKDIR) $(OBJS_DIR)
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
