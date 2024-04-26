/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:51:50 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 05:53:13 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespace(void)
{
	char	*input;

	input = g_shell->input;
	while (ft_isspace(input[g_shell->lexer_idx]))
		g_shell->lexer_idx++;
}

t_token_type	peek(void)
{
	char	*input;

	skip_whitespace();
	input = g_shell->input + g_shell->lexer_idx;
	if (*input == '\0')
		return (T_EOF);
	if (ft_strncmp(input, ">>", 2) == 0)
		return (T_APPEND);
	if (ft_strncmp(input, "<<", 2) == 0)
		return (T_HEREDOC);
	if (*input == '>')
		return (T_REDIR_OUT);
	if (*input == '<')
		return (T_REDIR_IN);
	if (*input == '|')
		return (T_PIPE);
	else
		return (T_WORD);
}
