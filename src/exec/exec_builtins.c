/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:47:20 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/09 13:57:22 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(t_cmd *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", "history", NULL};
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

void	ft_exec_builtins(t_cmd *cmd, bool should_exit)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->argv[0], "history") == 0)
		ft_history(cmd);
	else if (cmd->argc == 2 && !ft_strcmp(cmd->argv[0], "history")
		&& !ft_strcmp(cmd->argv[1], "-c"))
		ft_clear_history();
	if (should_exit)
		exit(0);
}

int	ft_exec_builtin(t_cmd *cmd, t_redir *io)
{
	int		pid;
	int		status;
	bool	is_exit;

	is_exit = ft_strcmp(cmd->argv[0], "exit") == 0;
	if (is_exit || !io)
	{
		ft_exec_builtins(cmd, false);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		if (ft_redirect(io, true))
			exit(1);
		ft_exec_builtins(cmd, true);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
