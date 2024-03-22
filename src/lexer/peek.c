#include "minishell.h"

t_token	*peek(t_lexer *l)
{
	size_t	initial_cur;
	t_token	*token;

	initial_cur = l->cur;
	token = get_next_token(l);
	l->cur = initial_cur;
	return (token);
}
