/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:37:52 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:38:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_file(const char *file)
{
	int			fd;
	struct stat	file_info;

	if (access(file, F_OK | R_OK) != 0)
		return (false);
	fd = open(file, O_RDONLY);
	if (fstat(fd, &file_info) < 0)
		return (close(fd), false);
	close(fd);
	return (S_ISREG(file_info.st_mode));
}

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	if (!cmd)
		return (NULL);
	i = 0;
	result = NULL;
	cmd = ft_expand(cmd, true);
	if (ft_strchr(cmd, '/') != NULL && check_file(cmd))
		return (cmd);
	path = ft_split(get_env("PATH"), ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		result = ft_strjoin(path[i], slash_cmd);
		if (check_file(result))
			break ;
		free(result);
		result = NULL;
		i++;
	}
	(free(slash_cmd), free_tab(path), free(cmd));
	return (result);
}
