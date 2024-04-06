/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 05:02:12 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tab(cmd->argv);
	free(cmd->path);
	free(cmd);
}

static void	free_io(t_redir *io)
{
	if (!io)
		return ;
	free(io->file);
	free_io(io->next);
	free(io);
}

void	free_tree(t_node *root)
{
	if (!root)
		return ;
	free_cmd(root->cmd);
	free_io(root->redir);
	free_tree(root->left);
	free_tree(root->right);
}
