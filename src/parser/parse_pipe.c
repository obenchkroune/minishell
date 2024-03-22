#include "minishell.h"

t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = create_node(N_PIPE, NULL, NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*parse_pipe(t_lexer *lexer)
{
	t_token			*token;
	t_node			*node;
	t_token_type	type;

	node = create_cmd_node(lexer);
	type = peek(lexer);
	if (type == T_PIPE)
	{
		token = get_next_token(lexer);
		node = create_pipe_node(node, parse_pipe(lexer));
		free(token);
	}
	return (node);
}
