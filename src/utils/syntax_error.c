/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 10:04:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(char *msg)
{
	t_token	token;

	if (msg)
		ft_fprintf(2, RED "minishell: " RESET "%s\n", msg);
	else
	{
		token = get_next_token();
		ft_fprintf(STDERR_FILENO,
			RED "minishell: " RESET "syntax error near unexpected token `%s'\n",
			token.value);
		if (token.type == T_WORD)
			free(token.value);
	}
	g_shell->has_syntax_error = true;
	set_status(1);
	g_shell->lexer_idx = ft_strlen(g_shell->input);
}
