/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 05:02:39 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_shell(void)
{
	free(g_shell->cwd);
	g_shell->cwd = NULL;
	free_tab(g_shell->envp);
	g_shell->envp = NULL;
	free(g_shell->prompt);
	g_shell->prompt = NULL;
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	free_tree(g_shell->tree);
	g_shell->tree = NULL;
	free(g_shell->input);
	g_shell->input = NULL;
	g_shell->lexer_idx = 0;
}