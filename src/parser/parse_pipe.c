#include "minishell.h"

t_node	*create_pipe(t_node *left, t_node *right)
{
	t_node	*node;

	node = create_node(N_PIPE, NULL, NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*parse_pipe(t_lexer *lexer)
{
	t_token	*token;
	t_node	*node;
	t_io	*io;

	io = parse_io(lexer);
	token = get_next_token(lexer);
	node = create_node(N_CMD, parse_cmd(token), io);
	// free(token);
	token = get_next_token(lexer);
	if (token && token->type == T_PIPE)
	{
		node = create_pipe(node, parse_pipe(lexer));
		// free(token);
	}
	return (node);
}
