/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:38 by oussama           #+#    #+#             */
/*   Updated: 2024/04/23 21:46:17 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(char *name)
{
	char	**envp;
	size_t	len;
	char	*equal_sign;

	if (*name == '?')
		return (ft_itoa(g_shell->last_exit_status));
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
