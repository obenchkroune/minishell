/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:27:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/18 04:03:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_env(char **envp)
{
	char	**result;
	size_t	len;
	size_t	i;

	len = ft_tabsize(envp);
	result = ft_calloc(sizeof(char *), len + 1);
	if (!result)
		panic("malloc");
	i = 0;
	while (i < len)
	{
		result[i] = ft_strdup(envp[i]);
		i++;
	}
	return (result);
}
