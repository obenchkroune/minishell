/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/19 07:50:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"

static bool	handle_unclosed_quote(size_t *i)
{
	char	quote;

	quote = g_shell->input[*i];
	if (quote != 0 && !ft_strchr("'\"", quote))
		return (false);
	while (g_shell->input[*i] && !ft_strchr(g_shell->input + *i + 1, quote))
	{
		if (!read_quote_completion(quote))
			return (false);
	}
	return (true);
}

static bool	handle_quoted_word(size_t *i)
{
	char	*pair_quote;

	pair_quote = ft_strchr(g_shell->input + *i + 1, g_shell->input[*i]);
	if (!pair_quote)
	{
		if (!handle_unclosed_quote(i))
			return (false);
	}
	pair_quote = ft_strchr(g_shell->input + *i + 1, g_shell->input[*i]);
	*i = pair_quote - g_shell->input + 1;
	return (true);
}

static t_token	get_word_token(void)
{
	size_t	start;
	char	*value;
	size_t	i;

	start = g_shell->lexer_idx;
	i = g_shell->lexer_idx;
	while (g_shell->input[i] && !ft_strchr(">|< ()&", g_shell->input[i]))
	{
		if (g_shell->input[i] && ft_strchr("'\"", g_shell->input[i]))
		{
			if (!handle_quoted_word(&i))
			{
				return ((t_token){.type = T_ERROR, .value = NULL});
			}
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
