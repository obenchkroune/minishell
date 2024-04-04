/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:47:20 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 00:47:21 by yaharkat         ###   ########.fr       */
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
	size_t	len;

	len = ft_strlen(args[0]);
	if (ft_strncmp(args[0], "echo", len) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "cd", len) == 0)
		ft_cd(args);
	else if (ft_strncmp(args[0], "pwd", len) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "export", len) == 0)
		ft_export(args);
	else if (ft_strncmp(args[0], "unset", len) == 0)
		ft_unset(args);
	else if (ft_strncmp(args[0], "env", len) == 0)
		ft_env();
	else if (ft_strncmp(args[0], "exit", len) == 0)
		ft_exit();
}
