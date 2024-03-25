/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:36:34 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 22:36:25 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_command(t_token **token)
{
	t_cmd	*cmd;

	if ((*token)->kind != T_WORD)
		panic("invalid syntax!");
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		panic("malloc");
	cmd->argv = parse_argv(token);
	cmd->path = get_executable(cmd->argv[0]);
	return (cmd);
}

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;

	node = create_cmd_node(parse_command(token));
	if (*token && (*token)->kind == T_PIPE)
	{
		*token = (*token)->next;
		node = create_node(N_PIPE, node, parse_pipe(token));
	}
	return (node);
}

t_node	*parse_input(char *input)
{
	t_token *tokens;
	t_token	*tokens_head;
	t_node	*tree;

	tokens = tokenize(input);
	tokens_head = tokens;
	tree = parse_pipe(&tokens);
	free_tokens(tokens_head);
	return (tree);
}
