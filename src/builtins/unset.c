/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:56:07 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/06 04:24:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_idx(char *key)
{
	char	**envp;
	size_t	len;
	int		i;

	envp = g_shell->envp;
	i = 0;
	while (envp && envp[i])
	{
		len = ft_strlen(key);
		if (ft_strncmp(key, envp[i], len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env(int idx)
{
	int	i;
	int	len;

	len = ft_tabsize(g_shell->envp);
	i = idx;
	free(g_shell->envp[i]);
	while (i < len - 1)
	{
		g_shell->envp[i] = g_shell->envp[i + 1];
		i++;
	}
	g_shell->envp[i] = NULL;
}

void	ft_unset(char **args)
{
	int		idx;

	while (args && *args)
	{
		idx = get_idx(*args);
		if (idx == -1)
		{
			args++;
			continue ;
		}
		remove_env(idx);
		args++;
	}
}
