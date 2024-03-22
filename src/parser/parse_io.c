#include "minishell.h"

bool	is_io_token(t_token_type type)
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

t_io	*parse_io(t_lexer *l)
{
	t_token	*token;
	t_io	*io;

	token = peek(l);
	io = NULL;
	if (!token || !is_io_token(token->type))
	{
		// free(token);
		return (NULL);
	}
	token = get_next_token(l);
	while (token && is_io_token(token->type))
	{
		append_io(&io, create_io(token->value, -1, token->type));
		// free(token);
	}
	return (io);
}