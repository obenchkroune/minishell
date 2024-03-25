/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 03:50:10 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/24 05:44:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_meta_char(char c)
{
	return (ft_strchr("<>|&;$\\", c));
}

bool	is_word_char(char c)
{
	return (!ft_isspace(c) && !is_meta_char(c));
}

char	*get_quoted_word(t_lexer *lexer)
{
	size_t	start;
	char	*pair_quote;
	size_t	len;

	start = lexer->i;
	if (!ft_strchr("'\"", lexer->val[start]))
		return (NULL);
	pair_quote = ft_strchr(lexer->val + start + 1, lexer->val[start]);
	if (pair_quote == NULL)
		panic("Unclosed quote");
	len = pair_quote - (lexer->val + start) + 1;
	lexer->i += len;
	return (ft_substr(lexer->val, start, len));
}
