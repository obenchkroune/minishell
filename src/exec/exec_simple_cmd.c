/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/09 01:27:45 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_fork(t_node *node)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = node->cmd;
	redir = node->redir;
	ft_redirect(redir, false);
	if (!cmd)
		exit(0);
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
		g_shell->last_exit_status = ft_exec_builtin(cmd, tree->redir);
		return (g_shell->last_exit_status);
	}
	status = ft_exec_cmd(tree);
	if (is_pipe)
		exit(status);
	g_shell->last_exit_status = status;
	return (status);
}
