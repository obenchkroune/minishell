/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_btree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:20:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 22:30:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
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

static void	free_io(t_io *io)
{
	if (!io)
		return ;
	free(io->file);
	free_io(io->next);
	free(io);
}

void	free_btree(t_node *root)
{
	if (!root)
		return ;
	free_cmd(root->cmd);
	free_io(root->io);
	free_btree(root->left);
	free_btree(root->right);
}
