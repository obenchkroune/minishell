NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(HEAD)

OBJS_DIR	=	./obj
SRCS_DIR	=	./src

# SRC_FILES	=	$(shell find src -type f -name '*.c')

HEAD		=	-I includes -I ~/.local/include
SRCS		=	$(shell find src -type f -name '*.c') #$(addprefix ./src/, $(SRC_FILES))
CLIBS		=	-Llibft -lft -L ~/.local/lib -lreadline -lcurses
OBJS		=	$(patsubst ./src/%.c, ./obj/%.o, $(SRCS))


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
