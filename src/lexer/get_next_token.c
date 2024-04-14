/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/12 16:10:04 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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
	char	*str;

	str = g_shell->input;
	i = g_shell->lexer_idx;
	start = i;
	while (str[i] && !ft_strchr(">|< ", str[i]))
	{
		if (str[i] && ft_strchr("'\"", str[i]))
		{
			if (!ft_strchr(str + i + 1, str[i]))
				return ((t_token){.type = T_ERROR, value = ft_substr(str + i, 0, 1)});
			i = ft_strchr(str + i + 1, str[i]) -str + 1;
			continue ;
		}
		i++;
	}
	value = ft_substr(str + start, 0, i - start);
	g_shell->lexer_idx = i;
	return ((t_token){.type = T_WORD, .value = value});
}

t_token_type	peek(void)
{
	char	*input;

	skip_whitespace();
	input = g_shell->input;
	if (input[g_shell->lexer_idx] == '\0')
		return (T_EOF);
	if (ft_strcmp(input, ">>") == 0)
		return (T_APPEND);
	if (ft_strcmp(input, "<<") == 0)
		return (T_HEREDOC);
	if (input[g_shell->lexer_idx] == '>')
		return (T_REDIR_OUT);
	if (input[g_shell->lexer_idx] == '<')
		return (T_REDIR_IN);
	if (input[g_shell->lexer_idx] == '|')
		return (T_PIPE);
	else
		return (T_WORD);
}

t_token	get_next_token(void)
{
	char	*input;

	skip_whitespace();
	input = g_shell->input + g_shell->lexer_idx;
	if (*input == '\0')
		return (g_shell->lexer_idx = 0,
			(t_token){.type = T_EOF, .value = NULL});
	else if (ft_strcmp(input, ">>") == 0)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_APPEND, .value = ">>"});
	else if (ft_strcmp(input, "<<") == 0)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_HEREDOC, .value = "<<"});
	else if (*input == '>')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_OUT, .value = ">"});
	else if (*input == '<')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_IN, .value = "<"});
	else if (*input == '|')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_PIPE, .value = "|"});
	else
		return (get_word_token());
}
