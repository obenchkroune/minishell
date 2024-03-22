/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:12:43 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 04:12:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	peek(t_lexer *lexer)
{
	size_t			initial_cur;
	t_token			*token;
	t_token_type	type;

	initial_cur = lexer->cur;
	token = get_next_token(lexer);
	if (!token)
		return (-1);
	lexer->cur = initial_cur;
	type = token->type;
	free(token);
	return (type);
}
