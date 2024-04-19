/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 11:34:47 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define SYNTAX_ERROR \
RED "minishell: " RESET "syntax error near unexpected token `%s'\n"

void	syntax_error(char *msg)
{
	t_token	token;

	if (msg)
		ft_fprintf(2, RED "minishell: " RESET "%s\n", msg);
	else
	{
		token = get_next_token();
		ft_fprintf(2, SYNTAX_ERROR, token.value);
		if (token.type == T_WORD)
			free(token.value);
	}
	g_shell->has_syntax_error = true;
	g_shell->last_exit_status = 1;
	g_shell->lexer_idx = ft_strlen(g_shell->input) - 1;
}
