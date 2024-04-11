/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:38 by oussama           #+#    #+#             */
/*   Updated: 2024/04/11 18:38:28 by oussama          ###   ########.fr       */
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
