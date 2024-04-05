/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:56:07 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 05:25:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char **args)
{
	t_env	*env;
	t_env	*prev;

	env = g_shell->env;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, args[1]) == 0)
		{
			if (!prev)
				return ;
			prev->next = env->next;
			ft_bzero(env->key, ft_strlen(env->key));
			ft_bzero(env->value, ft_strlen(env->value));
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}
