/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_valid_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:55:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/09 22:54:41 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	check_redirection(t_token *token);
static bool	check_pipe(t_token *token);
static bool	has_valid_quotes(t_token *tail);

bool	has_valid_syntax(t_token *token)
{
	t_token	*tail;

	while (token)
	{
		if (!token->next)
			tail = token;
		if (check_redirection(token) || check_pipe(token))
			return (false);
		token = token->next;
	}
	return (has_valid_quotes(tail));
}

static bool	is_redirection_token(t_token_type type)
{
	return (type == T_REDIRECT_OUT || type == T_REDIRECT_OUT_APPEND || \
			type == T_REDIRECT_IN || type == T_HEREDOC);
}

static bool	check_redirection(t_token *token)
{
	if (is_redirection_token(token->type))
		return (!token->next || token->next->type != T_WORD);
	return (false);
}

static bool	check_pipe(t_token *token)
{
	if (token->type == T_PIPE)
		return (!token->next || !token->prev);
	return (false);
}

static bool	has_valid_quotes(t_token *tail)
{
	size_t	last_idx;

	last_idx = ft_strlen(tail->value) - 1;
	if (ft_strchr("'\"", tail->value[0]) && \
		(last_idx == 0 || tail->value[last_idx] != tail->value[0]))
		return (false);
	return (true);
}
