/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 22:53:24 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_display_line(void)
{
	char	*display_line;
	char	*folder;
	char	*temp;

	folder = ft_strrchr(g_shell->cwd, '/');
	if (folder)
		display_line = ft_strjoin(GREEN "➜  " RESET "\e[1m" CYAN, folder + 1);
	else
		display_line = ft_strjoin(GREEN "➜  " RESET "\e[1m" CYAN, g_shell->cwd);
	temp = display_line;
	display_line = ft_strjoin(display_line, " \e[m" RESET);
	free(temp);
	return (display_line);
}
