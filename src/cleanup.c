/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:52:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/31 08:43:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_shell(void)
{
	free_env(g_shell->env);
	free(g_shell);
}

void	cleanup_rotation(void)
{
	free_tree(g_shell->nodes);
	free(g_shell->input);
}
