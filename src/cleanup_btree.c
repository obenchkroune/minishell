/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_btree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:20:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 22:59:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tab(cmd->argv);
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
