/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/22 22:26:21 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_meta_token(t_token_type type)
{
	return (type == T_SEMICOL || type == T_PIPE || type == T_AND
		|| type == T_OR);
}

t_node	*parse_meta(t_node *node, bool in_subshell)
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
		if (peek() == T_EOF && type != N_SEMICOL)
			return (syntax_error(NULL), node);
		node = create_node(type, node, parse_ast(in_subshell));
	}
	return (node);
}

bool	is_redir_token(t_token_type type)
{
	return (type == T_APPEND || type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_HEREDOC);
}

t_node	*parse_ast(bool in_subshell)
{
	t_node	*node;

	node = NULL;
	if (peek() == T_OPEN_PAREN)
	{
		in_subshell = true;
		get_next_token();
		node = create_node(N_SUBSHELL, parse_ast(in_subshell), NULL);
		if (peek() != T_CLOSE_PAREN)
			return (syntax_error("Unclosed Parenthesis"), node);
		get_next_token();
		in_subshell = false;
		if (!is_meta_token(peek()) && peek() != T_EOF)
			return (syntax_error(NULL), node);
	}
	else
		node = parse_cmd();
	if ((!in_subshell && peek() == T_CLOSE_PAREN) || peek() == T_OPEN_PAREN)
		return (syntax_error(NULL), node);
	node = parse_meta(node, in_subshell);
	return (node);
}
