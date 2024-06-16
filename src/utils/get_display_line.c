/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/16 14:23:36 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_display_line(void)
{
	char	*display_line;
	char	*temp;
	char	*cwd;
	char	*minishell;

	minishell = CYAN COLOR_BOLD "minishell: " COLOR_OFF RESET;
	if (g_shell->last_exit.status != 0)
		minishell = RED COLOR_BOLD "minishell: " COLOR_OFF RESET;
	cwd = ft_strreplace(g_shell->cwd, g_shell->home, "~");
	temp = ft_strjoin(minishell, cwd);
	display_line = ft_strjoin(temp, "$ ");
	(free(cwd), free(temp));
	return (display_line);
}
