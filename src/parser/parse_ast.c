/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/19 16:12:06 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include <time.h>

bool	is_meta_token(t_token_type type)
{
	return (type == T_SEMICOL || type == T_PIPE || type == T_AND
		|| type == T_OR);
}

t_node	*parse_meta(t_node *node)
{
	if (peek() == T_SEMICOL)
	{
		get_next_token();
		node = create_node(N_SEMICOL, node, parse_ast());
	}
	else if (peek() == T_PIPE)
	{
		get_next_token();
		read_unclosed_pipe(T_EOF);
		node = create_node(N_PIPE, node, parse_ast());
	}
	else if (peek() == T_AND)
	{
		get_next_token();
		node = create_node(N_AND, node, parse_ast());
	}
	else if (peek() == T_OR)
	{
		get_next_token();
		node = create_node(N_OR, node, parse_ast());
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
	t_node			*node;

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
	if (node && peek() != T_EOF)
		node = parse_meta(node);
	return (node);
}
