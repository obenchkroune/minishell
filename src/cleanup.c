/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:52:15 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/30 09:00:48 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
