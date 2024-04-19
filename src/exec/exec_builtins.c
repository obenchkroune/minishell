/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:47:20 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 05:54:23 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(t_cmd *cmd)
{
	const char *builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	size_t		i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	ft_exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd);
	else if (cmd->argc == 1 && !ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd();
	else if (cmd->argc == 2 && !ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd);
	else if (cmd->argc == 2 && !ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd);
	else if (cmd->argc == 1 && !ft_strcmp(cmd->argv[0], "env"))
		ft_env();
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd);
	else if (!ft_strcmp(cmd->argv[0], "history") && !cmd->argv[1])
		ft_history();
	// else if (cmd->argc == 2 && !ft_strcmp(cmd->argv[0], "history")
	// 	&& !ft_strcmp(cmd->argv[1], "-c"))
	// 	ft_clear_history();
	else
		panic_minishell("too many arguments", 1);
}
