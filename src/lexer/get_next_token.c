/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_token	get_word_token(void)
{
	size_t	start;
	char	*value;
	size_t	i;
	char	*pair_quote;

	start = g_shell->lexer_idx;
	i = g_shell->lexer_idx;
	while (g_shell->input[i] && !ft_strchr(">|< ()&", g_shell->input[i]))
	{
		if (g_shell->input[i] && ft_strchr("'\"", g_shell->input[i]))
		{
			pair_quote = ft_strchr(g_shell->input + i + 1, g_shell->input[i]);
			if (!pair_quote)
				return (syntax_error("unclosed quote"),
					(t_token){.type = T_ERROR});
			i = pair_quote - g_shell->input + 1;
			continue ;
		}
		i++;
	}
	value = ft_substr(g_shell->input + start, 0, i - start);
	g_shell->lexer_idx = i;
	return ((t_token){.type = T_WORD, .value = value});
}

t_token	get_redir_token(t_token t)
{
	if (t.type == T_APPEND)
		return (g_shell->lexer_idx += 2, t.value = ">>", t);
	else if (t.type == T_HEREDOC)
		return (g_shell->lexer_idx += 2, t.value = "<<", t);
	else if (t.type == T_REDIR_OUT)
		return (g_shell->lexer_idx += 1, t.value = ">", t);
	else if (t.type == T_REDIR_IN)
		return (g_shell->lexer_idx += 1, t.value = "<", t);
	else
		return (get_word_token());
}

t_token	get_next_token(void)
{
	t_token	t;

	t.type = peek();
	if (t.type == T_EOF)
		return (g_shell->lexer_idx = 0, t.value = "newline", t);
	else if (t.type == T_AND)
		return (g_shell->lexer_idx += 2, t.value = "&&", t);
	else if (t.type == T_OR)
		return (g_shell->lexer_idx += 2, t.value = "||", t);
	else if (t.type == T_PIPE)
		return (g_shell->lexer_idx += 1, t.value = "|", t);
	else if (t.type == T_SEMICOL)
		return (g_shell->lexer_idx += 1, t.value = ";", t);
	else if (t.type == T_OPEN_PAREN)
		return (g_shell->lexer_idx += 1, t.value = "(", t);
	else if (t.type == T_CLOSE_PAREN)
		return (g_shell->lexer_idx += 1, t.value = ")", t);
	return (get_redir_token(t));
}
