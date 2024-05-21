/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 05:51:50 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	skip_whitespace(void)
{
	char	*input;

	input = g_shell->input;
	while (ft_isspace(input[g_shell->lexer_idx]))
		g_shell->lexer_idx++;
}

static t_token_type	peek_redir_token(char *input)
{
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
	else
		return (T_WORD);
}

t_token_type	peek(void)
{
	char	*input;

	if (g_shell->has_syntax_error)
		return (T_EOF);
	skip_whitespace();
	input = g_shell->input + g_shell->lexer_idx;
	if (ft_strncmp(input, "&&", 2) == 0)
		return (T_AND);
	if (ft_strncmp(input, "||", 2) == 0)
		return (T_OR);
	if (*input == '|')
		return (T_PIPE);
	if (*input == ';')
		return (T_SEMICOL);
	if (*input == '(')
		return (T_OPEN_PAREN);
	if (*input == ')')
		return (T_CLOSE_PAREN);
	return (peek_redir_token(input));
}
