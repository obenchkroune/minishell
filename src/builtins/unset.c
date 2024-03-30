/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 08:56:07 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:35:53 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(char **args)
{
	t_env	*env;
	t_env	*prev;

	env = g_shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, args[1], ft_strlen(args[1])) == 0)
		{
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
