/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 04:41:51 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value, size_t idx)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		panic("malloc");
	token->type = type;
	token->value = value;
	token->idx = idx;
	return (token);
}

static t_token	*cmd_token(t_lexer *lexer)
{
	size_t	start;
	size_t	len;

	start = lexer->cur;
	while (!ft_strchr("<>|&", lexer->input[lexer->cur]))
		lexer->cur++;
	len = lexer->cur - start;
	return (create_token(T_CMD, ft_substr(lexer->input, start, len), start));
}

static char	*get_next_word(t_lexer *lexer)
{
	char	*pair_quote;
	size_t	start;

	while (ft_isspace(lexer->input[lexer->cur]))
		lexer->cur++;
	start = lexer->cur;
	if (ft_strchr("<>|&", lexer->input[start]) || lexer->input[start] == '\0')
		syntax_error("unexpected syntax", lexer->input, lexer->cur);
	if (ft_strchr("'\"", lexer->input[lexer->cur]))
	{
		lexer->cur++;
		pair_quote = ft_strchr(lexer->input + lexer->cur,
				lexer->input[lexer->cur - 1]);
		if (!pair_quote)
			syntax_error("unclosed quote", lexer->input, lexer->cur - 1);
		lexer->cur = pair_quote - lexer->input + 1;
		return (ft_substr(lexer->input, start, lexer->cur - start));
	}
	while (lexer->input[lexer->cur]
		&& !ft_strchr("<>|& \t", lexer->input[lexer->cur]))
		lexer->cur++;
	return (ft_substr(lexer->input, start, lexer->cur - start));
}

static t_token	*meta_token(t_lexer *lexer)
{
	char	*current;

	current = &lexer->input[lexer->cur];
	if (ft_strncmp(current, ">>", 2) == 0)
		return (lexer->cur += 2, create_token(T_APPEND, get_next_word(lexer), lexer->cur));
	else if (ft_strncmp(current, "<<", 2) == 0)
		return (lexer->cur += 2, create_token(T_HEREDOC, get_next_word(lexer), lexer->cur));
	else if (ft_strncmp(current, "||", 2) == 0)
		return (lexer->cur += 2, create_token(T_OR, NULL, lexer->cur));
	else if (ft_strncmp(current, "&&", 2) == 0)
		return (lexer->cur += 2, create_token(T_AND, NULL, lexer->cur));
	else if (*current == '>')
		return (lexer->cur++, create_token(T_OUT, get_next_word(lexer), lexer->cur));
	else if (*current == '|')
		return (lexer->cur++, create_token(T_PIPE, NULL, lexer->cur));
	else if (*current == '<')
		return (lexer->cur++, create_token(T_IN, get_next_word(lexer), lexer->cur));
	return (NULL);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (ft_isspace(lexer->input[lexer->cur]))
		lexer->cur++;
	if (lexer->input[lexer->cur] == '\0')
		return (NULL);
	if (ft_strchr("<>|&", lexer->input[lexer->cur]))
		return (meta_token(lexer));
	return (cmd_token(lexer));
}
