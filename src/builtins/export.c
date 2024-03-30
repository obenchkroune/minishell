/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 09:36:39 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(char **args)
{
	t_env	*env;
	t_env	*new;

	env = g_shell->env;
	while (env->next)
		env = env->next;
	new = create_env(args[1], args[2]);
	new->key = ft_strdup(args[1]);
	new->value = ft_strdup(args[2]);
	new->next = NULL;
	env->next = new;
}
