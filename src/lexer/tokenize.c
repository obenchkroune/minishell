/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:12:53 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/15 08:31:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tok	*tokenize(char *input)
{
	t_tok	*tokens;
	t_tok	*next_token;

	tokens = NULL;
	next_token = get_next_token(input);
	while (next_token)
	{
		append_token(&tokens, next_token);
		next_token = get_next_token(NULL);
	}
	return (tokens);
}
