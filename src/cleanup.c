/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:52:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/04 02:55:21 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_shell(void)
{
	free_env(g_shell->env);
	g_shell->env = NULL;
	free(g_shell->cwd);
	g_shell->cwd = NULL;
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	free_tree(g_shell->tree);
	g_shell->tree = NULL;
	free(g_shell->input);
	g_shell->input = NULL;
}
