/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:05:08 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 03:50:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char *name)
{
	char	**envp;
	size_t	len;
	char	*equal_sign;

	envp = g_shell->envp;
	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (!equal_sign)
		{
			envp++;
			continue ;
		}
		len = equal_sign - *envp;
		if (ft_strncmp(name, *envp, len) == 0)
			return (equal_sign + 1);
		envp++;
	}
	return (NULL);
}

void	add_env(char *key, char *value)
{
	size_t	len;
	size_t	i;
	char	**envp;
	char	*temp;

	len = ft_tabsize(g_shell->envp);
	envp = ft_calloc(sizeof(char *), len + 2);
	if (!envp)
		panic("malloc");
	i = 0;
	while (i < len)
	{
		envp[i] = ft_strdup(g_shell->envp[i]);
		i++;
	}
	temp = ft_strjoin(key, "=");
	envp[i] = ft_strjoin(temp, value);
	free(temp);
	// free_tab(g_shell->envp);
	g_shell->envp = envp;
}

void	set_env(char *key, char *value)
{
	size_t	len;
	char	*equal_sign;
	char	*temp;
	char	**envp;

	envp = g_shell->envp;
	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (!equal_sign)
		{
			envp++;
			continue ;
		}
		len = equal_sign - *envp;
		if (ft_strncmp(key, *envp, len) == 0)
		{
			free(*envp);
			temp = ft_strjoin(key, "=");
			*envp = ft_strjoin(temp, value);
			free(temp);
			return ;
		}
		envp++;
	}
	add_env(key, value);
}
