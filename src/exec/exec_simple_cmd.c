/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_fork(t_node *node)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = node->cmd;
	redir = node->redir;
	ft_redirect(redir, false);
	if (!cmd)
		exit(0);
	cmd->path = get_executable(cmd->argv[0]);
	if (!cmd->path)
	{
		(ft_fprintf(2, "minishell: %s: command not found\n", cmd->argv[0]),
			exit(127));
	}
	if (execve(cmd->path, cmd->argv, g_shell->envp) == -1)
	{
		(ft_putstr_fd(RED "minishell: " RESET, 2), perror(cmd->argv[0]),
			exit(1));
	}
}

static int	ft_exec_cmd(t_node *tree)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
		exec_fork(tree);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	ft_exec_simple_cmd(t_node *tree, bool is_pipe)
{
	int		status;
	t_cmd	*cmd;

	cmd = tree->cmd;
	if (cmd)
		expand_argv(cmd->argv);
	if (cmd && ft_is_builtin(cmd))
	{
		ft_exec_builtin(cmd, tree->redir);
		return (g_shell->last_exit.status);
	}
	status = ft_exec_cmd(tree);
	if (is_pipe)
		exit(status);
	set_status(status);
	return (status);
}
