/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:05:08 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/09 01:05:04 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_strrev(char *str)
{
	char	temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	printf("Here\n");
}

static void	last_exit_str(char *str, size_t size, int exit_status)
{
	size_t	i;

	i = 0;
	ft_bzero(str, size);
	if (exit_status == 0)
	{
		str[0] = '0';
		return ;
	}
	while (i < size && exit_status != 0)
	{
		str[i] = exit_status % 10 + '0';
		exit_status /= 10;
		i++;
	}
	ft_strrev(str);
}

char	*get_env(char *name)
{
	char	**envp;
	size_t	len;
	char	*equal_sign;

	if (*name == '?')
	{
		last_exit_str(g_shell->last_exit_status_str, 5,
			g_shell->last_exit_status);
		return (g_shell->last_exit_status_str);
	}
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
