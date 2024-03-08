/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:06:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/08 10:52:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_next_word(const char *input, bool is_env_var)
{
	size_t	i;
	char	*special_chars;

	i = 0;
	if (input[0] == '$')
		i++;
	special_chars = "_-";
	if (is_env_var)
		special_chars = "_";
	while ((ft_isalnum(input[i]) || \
		ft_strchr(special_chars, input[i])) && input[i] != '$')
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
	else if (*input == '$' && ft_isalnum(*(input + 1)))
		return (create_token(T_ENV_VAR, get_next_word(input, true)));
	else
		return (create_token(T_WORD, get_next_word(input, false)));
}

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
