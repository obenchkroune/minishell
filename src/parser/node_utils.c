/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:08:14 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/20 01:13:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*create_meta(t_node_type type, t_node *left, t_node *right)
{
	t_meta	*node;

	node = malloc(sizeof(t_meta));
	if (!node)
		panic("malloc");
	node->left = left;
	node->right = right;
	node->type = type;
	return ((t_node *)node);
}

t_node	*create_command(char *path, char **argv)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		panic("malloc");
	command->type = N_CMD;
	command->path = path;
	command->argv = argv;
	return ((t_node *)command);
}

t_node	*create_redir(t_node *cmd, t_token *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		panic("malloc");
	node->next = cmd;
	node->file = ft_strtrim(token->value, " <>");
	node->token_type = token->type;
	node->type = N_REDIR;
	return ((t_node *)node);
}
