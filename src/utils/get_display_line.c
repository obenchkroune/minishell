/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_display_line(void)
{
	char	*display_line;
	char	*header;
	char	*cwd;

	cwd = ft_strreplace(g_shell->cwd, g_shell->home, "~");
	header = ft_strjoin(CYAN COLOR_BOLD "minishell: " COLOR_OFF RESET, cwd);
	display_line = ft_strjoin(header, "$ ");
	(free(cwd), free(header));
	return (display_line);
}
