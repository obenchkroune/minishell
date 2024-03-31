/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:12:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/31 13:08:47 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)) || !ft_strncmp(cmd, "cd",
			ft_strlen(cmd)) || !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "export", ft_strlen(cmd)) || !ft_strncmp(cmd,
			"unset", ft_strlen(cmd)) || !ft_strncmp(cmd, "env", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (true);
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
