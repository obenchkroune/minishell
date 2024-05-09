/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:13:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 01:21:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_prompt(void)
{
	int	exit_status;

	g_shell->prompt = get_display_line();
	g_shell->input = readline(g_shell->prompt);
	if (!g_shell->input)
	{
		exit_status = g_shell->last_exit_status;
		cleanup_rotation();
		cleanup_shell();
		printf("exit\n");
		exit(exit_status);
	}
}
