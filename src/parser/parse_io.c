#include "minishell.h"

static bool	is_io_token(t_token_type type)
{
	return (type == T_APPEND || type == T_HEREDOC || type == T_IN || type == T_OUT);
}

void	append_io(t_io **root, t_io *io)
{
	t_io	*tail;

	if (!root || !io)
		return ;
	if (*root == NULL)
	{
		*root = io;
		return ;
	}
	tail = *root;
	while (tail->next)
	{
		tail = tail->next;
	}
	tail->next = io;
	io->prev = tail;
}

t_io	*parse_io(t_lexer *lexer)
{
	t_token			*token;
	t_token_type	type;
	t_io			*io;

	type = peek(lexer);
	io = NULL;
	if (!is_io_token(type))
		return (NULL);
	while (is_io_token(peek(lexer)))
	{
		token = get_next_token(lexer);
		append_io(&io, create_io_node(token->value, -1, token->type));
		free(token);
	}
	return (io);
}