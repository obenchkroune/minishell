/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/05 07:29:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exec_cmd(t_node *tree, char **args)
{
	int		status;
	pid_t	pid;
	t_cmd	*cmd;

	cmd = tree->cmd;
	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		if (tree->io)
			ft_redirect(tree->io);
		if (!cmd->path)
		{
			ft_fprintf(2, "minishell: %s: command not found\n", args[0]);
			exit(127);
		}
		if (execve(cmd->path, args, g_shell->envp) == -1)
		{
			ft_fprintf(2, "minishell: %s: %s\n", args[0], strerror(errno));
			exit(1);
		}
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_exec_simple_cmd(t_node *tree, bool is_pipe)
{
	int		status;
	char	**args;
	t_cmd	*cmd;

	cmd = tree->cmd;
	args = cmd->argv;
	if (ft_is_builtin(cmd->argv[0]))
	{
		ft_exec_builtin(args);
		return (0);
	}
	status = ft_exec_cmd(tree, args);
	if (is_pipe)
		exit(status);
	return (status);
}
