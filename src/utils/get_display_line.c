/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/23 21:44:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_display_line(void)
{
	char	*display_line;
	char	*header;
	char	*cwd;
	char	*home;

	home = get_env("HOME");
	if (home)
		cwd = ft_strreplace(g_shell->cwd, home, "~");
	else
		cwd = ft_strdup(g_shell->cwd);
	header = ft_strjoin(CYAN COLOR_BOLD "minishell: " COLOR_OFF RESET, cwd);
	display_line = ft_strjoin(header, "\n$ ");
	(free(cwd), free(header));
	return (display_line);
}
