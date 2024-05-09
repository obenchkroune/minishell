/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:02 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 00:38:47 by obenchkr         ###   ########.fr       */
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
	free_redir(redir->next);
	free(redir->file);
	close(redir->fd);
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

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
