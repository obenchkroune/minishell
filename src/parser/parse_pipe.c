/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 04:40:57 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unclosed_pipe(void)
{
	char	*input;
	char	*temp;

	input = readline("> ");
	if (!input)
		panic_minishell("syntax error: unexpected end of file", 2);
	temp = ft_strjoin(g_shell->input, input);
	g_shell->input = temp;
	free(g_shell->input);
	free(input);
}

t_node	*parse_pipe(void)
{
	t_node	*node;

	node = parse_cmd();
	if (!node)
		return (node);
	if (peek() == T_PIPE)
	{
		get_next_token();
		if (peek() == T_EOF)
			unclosed_pipe();
		node = create_node(N_PIPE, node, parse_pipe());
	}
	return (node);
}
