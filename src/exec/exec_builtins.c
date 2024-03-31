/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:12:37 by yaharkat          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/31 13:08:47 by yaharkat         ###   ########.fr       */
=======
/*   Updated: 2024/03/31 09:08:37 by obenchkr         ###   ########.fr       */
>>>>>>> 9e47469478f5512e2b0ad74af4ca09dc6a6d6e08
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *cmd)
{
	const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};

	while (*builtins)
	{
		if (!ft_strcmp(cmd, *builtins))
			return (true);
	}
	return (false);
}

void	ft_exec_builtin(char **args)
{
<<<<<<< HEAD
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(args[0], "exit") == 0)
=======
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(args[0], "exit") == 0)
>>>>>>> 9e47469478f5512e2b0ad74af4ca09dc6a6d6e08
		ft_exit();
}
