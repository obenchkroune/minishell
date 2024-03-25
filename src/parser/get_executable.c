/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:50:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 06:31:24 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;

	result = NULL;
	// printf("%s\n", get_env("PATH"));
	path = ft_split(get_env("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && *path)
	{
		result = ft_strjoin(*path, slash_cmd);
		if (access(result, F_OK) == 0)
			break ;
		free(result);
		result = NULL;
		path++;
	}
	free(slash_cmd);
	return (result);
}
