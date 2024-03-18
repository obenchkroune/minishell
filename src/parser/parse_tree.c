/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:08:25 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/18 04:13:28 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

t_node	*parse_redir(t_node *cmd, t_tok **tokens)
{
	while (*tokens && (*tokens)->type == T_REDIR_OUT)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->type != T_WORD)
			panic("syntax error!");
		cmd = create_redir(cmd, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_node	*parse_exec(t_tok **tokens)
{
	t_node	*node;

	if (!*tokens)
		panic("Syntax error");
	node = create_exec(NULL, NULL);
	node = parse_redir(node, tokens);
	while (*tokens && (*tokens)->type != T_WORD)
	{
		*tokens = (*tokens)->next;
	}
	node = parse_redir(node, tokens);
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
