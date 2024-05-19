/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/18 13:02:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_meta_token(t_token_type type)
{
	return (type == T_SEMICOL || type == T_PIPE || type == T_AND
		|| type == T_OR);
}

t_node	*parse_meta(t_node *node)
{
	if (!is_meta_token(peek()))
		return (syntax_error(NULL), node);
	if (peek() == T_SEMICOL)
	{
		get_next_token();
		node = create_node(N_SEMICOL, node, parse_pipe());
	}
	else if (peek() == T_PIPE)
	{
		get_next_token();
		read_unclosed_pipe(T_EOF);
		node = create_node(N_PIPE, node, parse_pipe());
	}
	else if (peek() == T_AND)
	{
		get_next_token();
		node = create_node(N_AND, node, parse_pipe());
	}
	else if (peek() == T_OR)
	{
		get_next_token();
		node = create_node(N_OR, node, parse_pipe());
	}
	return (node);
}

bool	is_redir_token(t_token_type type)
{
	return (type == T_APPEND || type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_HEREDOC);
}

t_node	*parse_pipe(void)
{
	t_node	*node;

	node = NULL;
	if (peek() == T_OPEN_PAREN)
	{
		get_next_token();
		if (peek() != T_WORD && !is_redir_token(peek()))
			return (syntax_error(NULL), node);
		node = create_node(N_SUBSHELL, parse_pipe(), NULL);
		if (peek() != T_CLOSE_PAREN)
			return (syntax_error(NULL), node);
		get_next_token();
	}
	else
		node = parse_cmd();
	if (node && peek() != T_EOF)
		node = parse_meta(node);
	return (node);
}
