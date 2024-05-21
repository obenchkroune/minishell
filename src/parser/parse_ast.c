/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 05:11:24 by obenchkr         ###   ########.fr       */
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
	t_node_type	type;

	type = INT_MAX;
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
	if (type != INT_MAX)
	{
		get_next_token();
		if (peek() != T_WORD && type != N_SEMICOL && !is_redir_token(peek()))
			return (syntax_error(NULL), node);
		node = create_node(type, node, parse_ast());
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

	node = NULL;
	if (peek() == T_OPEN_PAREN)
	{
		get_next_token();
		if (peek() != T_WORD && !is_redir_token(peek()))
			return (syntax_error(NULL), node);
		node = create_node(N_SUBSHELL, parse_ast(), NULL);
		if (peek() != T_CLOSE_PAREN)
			return (syntax_error(NULL), node);
		get_next_token();
		if (!is_meta_token(peek()) && peek() != T_EOF)
			return (syntax_error(NULL), node);
	}
	else
		node = parse_cmd();
	node = parse_meta(node);
	return (node);
}
