/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:47:42 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/29 04:57:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_io(t_io *node)
{
	if (!node)
		return ;
	free_io(node->next);
	free(node->file);
	free(node);
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
	free(cmd->path);
	free(cmd);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->type == N_CMD)
	{
		free_cmd(node->cmd);
		free_io(node->io);
	}
	free(node);
}
