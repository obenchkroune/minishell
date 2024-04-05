/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:50:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/05 06:03:58 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_executable(char *cmd)
{
	char	*result;
	char	**path;
	char	*slash_cmd;
	size_t	i;

	i = 0;
	result = NULL;
	if (get_env("PATH") == NULL)
		panic_minishell("PATH env variable is not found", 1);
	path = ft_split(get_env("PATH")->value, ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (path && path[i])
	{
		result = ft_strjoin(path[i], slash_cmd);
		if (access(result, F_OK) == 0)
			break ;
		free(result);
		result = NULL;
		i++;
	}
	free(slash_cmd);
	free_tab(path);
	return (result);
}
