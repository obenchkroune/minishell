/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 17:43:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unclosed_pipe(void)
{
	char	*input;
	char	*temp;

	g_shell->secondary_input = dup(0);
	write(1, "> ", 2);
	input = get_next_line(g_shell->secondary_input);
	input[ft_strlen(input) - 1] = '\0';
	if (!input)
		syntax_error("syntax error: unexpedted end of file");
	temp = append_input(g_shell->input, input);
	(free(g_shell->input), free(input));
	g_shell->input = temp;
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
		while (peek() == T_EOF && !g_shell->has_syntax_error)
			unclosed_pipe();
		node = create_node(N_PIPE, node, parse_pipe());
	}
	return (node);
}
