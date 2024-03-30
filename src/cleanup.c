/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:52:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/29 05:10:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_shell(void)
{
	free_env(g_shell->env);
	free(g_shell);
}

void	cleanup_rotation(char *input, t_node *nodes)
{
	free_tree(nodes);
	free(input);
}
