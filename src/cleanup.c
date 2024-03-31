/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:52:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/31 09:10:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_shell(void)
{
	free_env(g_shell->env);
	g_shell->env = NULL;
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	free_tree(g_shell->nodes);
	g_shell->nodes = NULL;
	free(g_shell->input);
	g_shell->input = NULL;
}
