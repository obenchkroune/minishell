/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:12:37 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/30 10:59:30 by yaharkat         ###   ########.fr       */
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
	if (args[0] == "echo")
		ft_echo(args);
	else if (args[0] == "cd")
		ft_cd(args);
	else if (args[0] == "pwd")
		ft_pwd();
	else if (args[0] == "export")
		ft_export(args);
	else if (args[0] == "unset")
		ft_unset(args);
	else if (args[0] == "env")
		ft_env();
	else if (args[0] == "exit")
		ft_exit();
}
