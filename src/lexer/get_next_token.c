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

#define SINGLE_QUOTE_ERR -1
#define DOUBLE_QUOTE_ERR -2

int	get_quoted_word_len(void)
{
	size_t	i;
	char	*str;
	char	*pair_quote;

	str = g_shell->input;
	i = g_shell->lexer_idx;
	pair_quote = ft_strchr(&str[i + 1], str[i]);
	if (!pair_quote)
	{
		g_shell->lexer_idx = ft_strlen(str);
		if (str[i] == '\'')
			return (SINGLE_QUOTE_ERR);
		return (DOUBLE_QUOTE_ERR);
	}
	return (pair_quote - &str[i] + 1);
}

// TODO: fix leaks
static t_token	get_quoted_word(void)
{
	size_t	start;
	char	*str;
	int		len;
	char	*value;
	char	*word;
	char	*temp;

	str = g_shell->input;
	start = g_shell->lexer_idx;
	value = NULL;
	while (str[start] && ft_strchr("\"'", str[start]))
	{
		len = get_quoted_word_len();
		if (len < 0)
		{
			if (len == SINGLE_QUOTE_ERR)
				return ((t_token){.type = T_ERROR, .value = "'"});
			return ((t_token){.type = T_ERROR, .value = "\""});
		}
		word = ft_substr(str, start + 1, len - 2);
		if (str[start] == '\'')
			word = ft_strreplace(word, "$", "$\\");
		temp = value;
		value = ft_strjoin(value, word);
		free(temp);
		free(word);
		g_shell->lexer_idx += len;
		start = g_shell->lexer_idx;
	}
	return ((t_token)
		{.type = T_WORD, .value = value});
}

static t_token	get_word_token(void)
{
	size_t	start;
	size_t	i;
	char	*value;
	char	*str;

	str = g_shell->input;
	i = g_shell->lexer_idx;
	if (str[i] && ft_strchr("\"'", str[i]))
		return (get_quoted_word());
	start = i;
	while (str[i] && !ft_strchr(">|< ", str[i]))
		i++;
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
	input = g_shell->input;
	if (input[g_shell->lexer_idx] == '\0')
		return (g_shell->lexer_idx = 0,
			(t_token){.type = T_EOF, .value = NULL});
	if (ft_strcmp(input, ">>") == 0)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_APPEND, .value = ">>"});
	if (ft_strcmp(input, "<<") == 0)
		return (g_shell->lexer_idx += 2,
			(t_token){.type = T_HEREDOC, .value = "<<"});
	if (input[g_shell->lexer_idx] == '>')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_OUT, .value = ">"});
	if (input[g_shell->lexer_idx] == '<')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_REDIR_IN, .value = "<"});
	if (input[g_shell->lexer_idx] == '|')
		return (g_shell->lexer_idx += 1,
			(t_token){.type = T_PIPE, .value = "|"});
	else
		return (get_word_token());
}
