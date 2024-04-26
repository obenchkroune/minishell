/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:13:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 10:32:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_prompt(void)
{
	g_shell->prompt = get_display_line();
	g_shell->input = readline(g_shell->prompt);
	if (!g_shell->input)
	{
		cleanup_rotation();
		cleanup_shell();
		printf("exit\n");
		exit(0);
	}
}
