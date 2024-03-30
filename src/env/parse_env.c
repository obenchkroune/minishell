/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:27:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/30 09:02:33 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*result;
	t_env	*tail;

	if (!env || !key || !value)
		return ;
	result = malloc(sizeof(t_env));
	if (!result)
		panic("malloc");
	result->key = key;
	result->value = value;
	result->next = NULL;
	if (!*env)
	{
		*env = result;
		return ;
	}
	tail = *env;
	while (tail->next)
		tail = tail->next;
	tail->next = result;
}

t_env	*parse_env(char **envp)
{
	t_env	*result;
	char	*equal_sign;

	result = NULL;
	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (equal_sign)
		{
			add_env(&result, ft_substr(*envp, 0, equal_sign - *envp),
				ft_strdup(equal_sign + 1));
		}
		envp++;
	}
	return (result);
}
