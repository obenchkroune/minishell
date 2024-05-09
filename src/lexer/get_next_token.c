/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 13:52:33 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_ERROR "syntax error: unexpected EOF while looking for matching"

static bool	handle_unclosed_quote(size_t *i)
{
	char	quote;
	char	*input;
	char	*value;

	quote = g_shell->input[*i];
	if (quote != 0 && !ft_strchr("'\"", quote))
		return (false);
	while (g_shell->input[*i] && !ft_strchr(g_shell->input + *i + 1, quote))
	{
		input = readline("> ");
		if (!input)
		{
			if (quote == '\'')
				syntax_error(QUOTE_ERROR " `''");
			else
				syntax_error(QUOTE_ERROR " `\"'");
			syntax_error("syntax error: unexpected end of file");
			return (false);
		}
		value = append_input(g_shell->input, input);
		(free(g_shell->input), free(input));
		g_shell->input = value;
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
	while (g_shell->input[i] && !ft_strchr(">|< ", g_shell->input[i]))
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

t_token	get_next_token(void)
{
	skip_whitespace();
	if (peek() == T_EOF)
		return (g_shell->lexer_idx = 0, (t_token){.type = T_EOF,
			.value = "newline"});
	else if (peek() == T_APPEND)
		return (g_shell->lexer_idx += 2, (t_token){.type = T_APPEND,
			.value = ">>"});
	else if (peek() == T_HEREDOC)
		return (g_shell->lexer_idx += 2, (t_token){.type = T_HEREDOC,
			.value = "<<"});
	else if (peek() == T_REDIR_OUT)
		return (g_shell->lexer_idx += 1, (t_token){.type = T_REDIR_OUT,
			.value = ">"});
	else if (peek() == T_REDIR_IN)
		return (g_shell->lexer_idx += 1, (t_token){.type = T_REDIR_IN,
			.value = "<"});
	else if (peek() == T_PIPE)
		return (g_shell->lexer_idx += 1, (t_token){.type = T_PIPE,
			.value = "|"});
	else
		return (get_word_token());
}
