/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:04:58 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/21 03:50:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND ||
		type == T_HEREDOC);
}

t_node	*parse_redir(t_node *node, t_token **token)
{
	while (*token || is_redir_token((*token)->type))
	{
		node = create_redir(node, *token);
		*token = (*token)->next;
	}
	return (node);
}

