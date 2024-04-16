/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 07:15:51 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

static void	skip_whitespace(void)
{
	char	*input;

	input = g_shell->input;
	while (ft_isspace(input[g_shell->lexer_idx]))
		g_shell->lexer_idx++;
}

static t_token	get_word_token(void)
{
	size_t	start;
	size_t	i;
	char	*value;
	char	*input;

	input = g_shell->input;
	i = g_shell->lexer_idx;
	start = i;
	while (input[i] && !ft_strchr(">|< ", input[i]))
	{
		if (input[i] && ft_strchr("'\"", input[i]))
		{
			if (!ft_strchr(input + i + 1, input[i]))
				return ((t_token){.type = T_ERROR,
					value = ft_substr(input + i, 0, 1)});
			i = ft_strchr(input + i + 1, input[i]) - input + 1;
			continue ;
		}
		i++;
	}
	value = ft_substr(input + start, 0, i - start);
	g_shell->lexer_idx = i;
	return ((t_token){.type = T_WORD, .value = value});
}

t_token_type	peek(void)
{
	char	*input;

	skip_whitespace();
	input = g_shell->input + g_shell->lexer_idx;
	if (*input == '\0')
		return (T_EOF);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (T_APPEND);
	if (ft_strncmp(input, "<<", 2) == 0)
		return (T_HEREDOC);
	if (*input == '>')
		return (T_REDIR_OUT);
	if (*input == '<')
		return (T_REDIR_IN);
	if (*input == '|')
		return (T_PIPE);
	else
		return (T_WORD);
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
