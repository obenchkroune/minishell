/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_display_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:26:18 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 04:26:41 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_user_host_line(void)
{
	char	*result;
	size_t	len;
	size_t	color_len;

	color_len = ft_strlen(GREEN) + ft_strlen(RESET);
	len = color_len + ft_strlen(g_shell->username)
		+ ft_strlen(g_shell->hostname) + 3;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		panic("malloc");
	ft_strlcat(result, CYAN, len + 1);
	ft_strlcat(result, g_shell->username, len + 1);
	ft_strlcat(result, "@", len + 1);
	ft_strlcat(result, g_shell->hostname, len + 1);
	ft_strlcat(result, RESET ": ", len + 1);
	return (result);
}

char	*get_display_line(void)
{
	char	*temp;
	char	*display_line;
	char	*user_host_line;

	user_host_line = get_user_host_line();
	temp = ft_strjoin(user_host_line, g_shell->cwd);
	free(user_host_line);
	display_line = ft_strjoin(temp, "\n\r$ ");
	free(temp);
	return (display_line);
}