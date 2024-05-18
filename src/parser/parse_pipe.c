/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 00:49:26 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/18 13:02:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_pipe(void)
{
	t_node	*node;

	node = parse_cmd();
	if (!node)
		return (node);
	if (peek() == T_SEMICOL)
	{
		get_next_token();
		node = create_node(N_SEMICOL, node, parse_pipe());
	}
	else if (peek() == T_PIPE)
	{
		get_next_token();
		read_unclosed_pipe(T_EOF);
		node = create_node(N_PIPE, node, parse_pipe());
	}
	return (node);
}
