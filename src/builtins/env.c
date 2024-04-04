/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:13:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 03:35:11 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(void)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		ft_fprintf(STDOUT_FILENO, "%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
