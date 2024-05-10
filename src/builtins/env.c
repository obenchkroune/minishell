/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:13:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/10 20:53:45 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
