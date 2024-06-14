/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:28:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_meta_token(t_token_type type)
{
	return (type == T_SEMICOL || type == T_PIPE || type == T_AND
		|| type == T_OR);
}

t_node	*parse_meta(t_node *node)
{
	int	type;

	type = -1;
	if (peek() == T_EOF)
		return (node);
	if (peek() == T_SEMICOL)
		type = N_SEMICOL;
	else if (peek() == T_PIPE)
		type = N_PIPE;
	else if (peek() == T_AND)
		type = N_AND;
	else if (peek() == T_OR)
		type = N_OR;
	if (type != -1)
	{
		get_next_token();
		if (peek() == T_EOF && type != N_SEMICOL)
			return (syntax_error(NULL), node);
		node = create_node(type, node, parse_cmd());
	}
	return (node);
}

bool	is_redir_token(t_token_type type)
{
	return (type == T_APPEND || type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_HEREDOC);
}

t_node	*parse_ast(void)
{
	t_node	*node;

	node = parse_cmd();
	while (peek() != T_EOF)
	{
		node = parse_meta(node);
	}
	return (node);
}
