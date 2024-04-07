/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 05:06:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tab(cmd->argv);
	free(cmd->path);
	free(cmd);
}

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free(redir->file);
	free_redir(redir->next);
	free(redir);
}

void	free_tree(t_node *root)
{
	if (!root)
		return ;
	free_cmd(root->cmd);
	free_redir(root->redir);
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
