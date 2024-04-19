/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 06:15:41 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_ERROR \
RED "minishell:" RESET \
"syntax error: unexpected EOF while looking for matching `%c'\n"

static char	*append_input(char *s1, char *s2)
{
	char	*value;

	s1 = ft_strjoin(s1, "\n");
	value = ft_strjoin(s1, s2);
	free(s1);
	return (value);
}

static int	handle_unclosed_quote(void)
{
	char	quote;
	char	*input;
	char	*value;

	quote = g_shell->input[g_shell->lexer_idx];
	if (quote != 0 && !ft_strchr("'\"", quote))
		return (-1);
	while (g_shell->input[g_shell->lexer_idx]
		&& !ft_strchr(g_shell->input + g_shell->lexer_idx + 1, quote))
	{
		input = readline("> ");
		if (!input)
		{
			g_shell->has_syntax_error = true;
			printf(QUOTE_ERROR, quote);
			return (g_shell->lexer_idx++, -1);
		}
		value = append_input(g_shell->input, input);
		free(g_shell->input);
		g_shell->input = value;
	}
	return (0);
}

static t_token	get_word_token(void)
{
	size_t	start;
	char	*value;
	char	*pair_quote;

	start = g_shell->lexer_idx;
	while (g_shell->input[g_shell->lexer_idx]
		&& !ft_strchr(">|< ", g_shell->input[g_shell->lexer_idx]))
	{
		if (g_shell->input[g_shell->lexer_idx]
			&& ft_strchr("'\"", g_shell->input[g_shell->lexer_idx]))
		{
			pair_quote = ft_strchr(g_shell->input + g_shell->lexer_idx + 1,
					g_shell->input[g_shell->lexer_idx]);
			if (!pair_quote)
				if (handle_unclosed_quote() == -1)
					return ((t_token){.type = T_ERROR, .value = NULL});
			g_shell->lexer_idx = pair_quote - g_shell->input + 1;
			continue ;
		}
		g_shell->lexer_idx++;
	}
	value = ft_substr(g_shell->input + start, 0, g_shell->lexer_idx - start);
	return ((t_token){.type = T_WORD, .value = value});
}

t_token	get_next_token(void)
{
	skip_whitespace();
	if (peek() == T_EOF)
		return (g_shell->lexer_idx = 0,
			(t_token){.type = T_EOF, .value = NULL});
	else if (peek() == T_APPEND)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_APPEND, .value = ">>"});
	else if (peek() == T_HEREDOC)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_HEREDOC, .value = "<<"});
	else if (peek() == T_REDIR_OUT)
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_OUT, .value = ">"});
	else if (peek() == T_REDIR_IN)
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_IN, .value = "<"});
	else if (peek() == T_PIPE)
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_PIPE, .value = "|"});
	else
		return (get_word_token());
}
