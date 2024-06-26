/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:38 by oussama           #+#    #+#             */
/*   Updated: 2024/05/22 19:34:01 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(const char *key)
{
	t_env	*env;

	env = g_shell->env;
	if (*key == '?')
		return (g_shell->last_exit.str);
	if (*key == '$')
		return (g_shell->process_id);
	if (ft_strcmp(key, "0") == 0)
		return (g_shell->shell_script);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
