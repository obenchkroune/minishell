/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:45:14 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/21 03:50:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;

	node = parse_command(token);
	if (*token && (*token)->type == T_PIPE)
	{
		*token = (*token)->next;
		node = create_meta(N_PIPE, node, parse_pipe(token));
	}
	return (node);
}

