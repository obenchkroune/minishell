/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:08:25 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/17 09:11:19 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_node	*parse_exec(t_tok **tokens)
{
	t_node	*node;

	if (!*tokens || (*tokens)->type != T_WORD)
		printf("Syntax error\n");
	node = create_exec(NULL, NULL);
	while (*tokens && (*tokens)->type == T_WORD)
		*tokens = (*tokens)->next;
	return (node);
}

t_node	*parse_pipes(t_tok **tokens)
{
	t_node	*node;

	node = parse_exec(tokens);
	if (*tokens && (*tokens)->type == T_PIPE)
	{
		*tokens = (*tokens)->next;
		node = create_pipe(node, parse_pipes(tokens));
	}
	return (node);
}

t_node	*parse_tree(t_tok **tokens)
{
	return (parse_pipes(tokens));
}
