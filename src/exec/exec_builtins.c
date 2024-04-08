/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:47:20 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/08 03:14:33 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd,
			"history"));
}

void	ft_exec_builtin(char **args)
{
	if (!args || !args[0])
		return ;
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (tab_len(args) <= 2 && !ft_strcmp(args[0], "cd"))
		ft_cd(args);
	else if (tab_len(args) == 1 && !ft_strcmp(args[0], "pwd"))
		ft_pwd();
	else if (tab_len(args) == 2 && !ft_strcmp(args[0], "export"))
		ft_export(args);
	else if (tab_len(args) == 2 && !ft_strcmp(args[0], "unset"))
		ft_unset(args);
	else if (tab_len(args) == 1 && !ft_strcmp(args[0], "env"))
		ft_env();
	else if (tab_len(args) == 1 && !ft_strcmp(args[0], "exit"))
		ft_exit();
	else if (!ft_strcmp(args[0], "history") && !args[1])
		ft_history();
	else if (tab_len(args) == 2 && !ft_strcmp(args[0], "history")
		&& !ft_strcmp(args[1], "-c"))
		ft_clear_history();
	else
		panic_minishell("too many arguments", 1);
}
