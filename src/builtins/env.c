/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:13:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	char	**envp;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("env: too many arguments!", 2);
		return ;
	}
	envp = g_shell->envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

t_env	*ft_dup_env(void)
{
	t_env	*shell_env;
	t_env	*result;

	shell_env = g_shell->env;
	result = NULL;
	while (shell_env)
	{
		add_env(&result, shell_env->key, shell_env->value);
		shell_env = shell_env->next;
	}
	return (result);
}
