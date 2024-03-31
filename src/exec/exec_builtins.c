/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:12:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/31 19:23:27 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit"};

	while (*builtins)
	{
		if (!ft_strncmp(cmd, *builtins, ft_strlen(*builtins)))
			return (true);
	}
	return (false);
}

void	ft_exec_builtin(char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(args);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit();
}
