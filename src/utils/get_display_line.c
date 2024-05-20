/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/20 19:19:36 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
