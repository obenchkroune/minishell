/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 05:32:13 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	cleanup_shell(void)
{
	free(g_shell->cwd);
	g_shell->cwd = NULL;
	free_tab(g_shell->envp);
	g_shell->envp = NULL;
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	if (g_shell->tree)
	{
		free_tree(g_shell->tree);
		g_shell->tree = NULL;
	}
	if (g_shell->input)
	{
		free(g_shell->input);
		g_shell->input = NULL;
	}
	if (g_shell->prompt)
	{
		free(g_shell->prompt);
		g_shell->prompt = NULL;
	}
	g_shell->lexer_idx = 0;
	g_shell->has_heredoc = false;
}
