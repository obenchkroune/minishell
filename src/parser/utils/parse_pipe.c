/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:22:32 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/28 01:22:39 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;

	node = parse_cmd(token);
	if (*token && (*token)->kind == T_PIPE)
	{
		*token = (*token)->next;
		node = create_node(N_PIPE, node, parse_pipe(token));
	}
	return (node);
}
