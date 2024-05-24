/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/24 03:52:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_display_line(void)
{
	char	*display_line;
	char	*temp;
	char	*cwd;

	cwd = ft_strreplace(g_shell->cwd, g_shell->home, "~");
	temp = ft_strjoin(CYAN COLOR_BOLD "minishell: " COLOR_OFF RESET, cwd);
	display_line = ft_strjoin(temp, "$ ");
	(free(cwd), free(temp));
	return (display_line);
}
