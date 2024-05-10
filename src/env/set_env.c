/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:05:08 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 12:21:32 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_env(char *key)
{
	t_env	*env;
	t_env	*prev;

	env = g_shell->env;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (!prev)
				g_shell->env = env->next;
			else
				prev->next = env->next;
			(free(env->key), free(env->value), free(env));
			update_envp();
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	set_env(char *key, char *value)
{
	t_env	*env;
	t_env	*tail;
	char	*temp;

	env = g_shell->env;
	tail = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			temp = env->value;
			env->value = ft_strdup(value);
			free(temp);
			update_envp();
			return ;
		}
		tail = env;
		env = env->next;
	}
	tail->next = env_constructor(key, value);
	update_envp();
}
