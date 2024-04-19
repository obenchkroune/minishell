/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:05:08 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 06:44:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free_tab(g_shell->envp);
	g_shell->envp = envp;
}

static char	*join_env(char *key, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

void	set_env(char *key, char *value)
{
	size_t	len;
	char	*equal_sign;
	char	**envp;

	if (!value)
		value = "";
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
			*envp = join_env(key, value);
			return ;
		}
		envp++;
	}
	add_env(key, value);
}
