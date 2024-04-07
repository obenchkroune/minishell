/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:27:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 02:16:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	add_env(t_env **env, char *key, char *value)
// {
// 	t_env	*result;
// 	t_env	*tail;

// 	if (!env || !key || !value)
// 		return ;
// 	result = malloc(sizeof(t_env));
// 	if (!result)
// 		panic("malloc");
// 	result->key = key;
// 	result->value = value;
// 	result->next = NULL;
// 	if (!*env)
// 	{
// 		*env = result;
// 		return ;
// 	}
// 	tail = *env;
// 	while (tail->next)
// 		tail = tail->next;
// 	tail->next = result;
// }

size_t	ft_tabsize(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

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
