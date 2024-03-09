/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:06:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/09 22:55:57 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*get_next_word(const char *input);
static char		*get_next_quoted_word(const char *input);
static t_token	*get_next_token(const char *input);

t_token	*tokenize(const char *input)
{
	t_token	*tokens;
	t_token	*tok;

	tokens = NULL;
	while (1)
	{
		while (*input == ' ' || *input == '\t')
			input++;
		tok = get_next_token(input);
		if (!tok)
			break ;
		input += ft_strlen(tok->value);
		add_token(&tokens, tok);
	}
	return (tokens);
}

static char	*get_next_word(const char *input)
{
	size_t	i;

	i = 0;
	while (!ft_strchr("><|& ", input[i]))
		i++;
	return (ft_substr(input, 0, i));
}

static char	*get_next_quoted_word(const char *input)
{
	char	*pair_quote;

	pair_quote = ft_strchr(input + 1, *input);
	if (!pair_quote)
		return (ft_strdup(input));
	return (ft_substr(input, 0, pair_quote - input + 1));
}

static t_token	*get_next_token(const char *input)
{
	if (*input == '\0')
		return (NULL);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (create_token(T_REDIRECT_OUT_APPEND, ">>"));
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (create_token(T_HEREDOC, "<<"));
	else if (*input == '>')
		return (create_token(T_REDIRECT_OUT, ">"));
	else if (*input == '<')
		return (create_token(T_REDIRECT_OUT, "<"));
	else if (*input == '|')
		return (create_token(T_PIPE, "|"));
	else if (*input == '\'' || *input == '"')
		return (create_token(T_WORD, get_next_quoted_word(input)));
	else
		return (create_token(T_WORD, get_next_word(input)));
}
