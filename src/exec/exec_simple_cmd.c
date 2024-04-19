/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 17:12:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirection_node(t_node *tree)
{
	return (tree->redir && (tree->redir->type == REDIR_IN
			|| tree->redir->type == REDIR_OUT
			|| tree->redir->type == REDIR_APPEND
			|| tree->redir->type == REDIR_HEREDOC));
}

static int	ft_exec_cmd(t_node *tree)
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
		if (is_redirection_node(tree))
			ft_redirect(tree->redir, false);
		if (!cmd)
			exit(0);
		if (!cmd->path)
			(ft_fprintf(2, "minishell: %s: command not found\n", cmd->argv[0]),
				exit(127));
		if (execve(cmd->path, cmd->argv, g_shell->envp) == -1)
			(perror(""), exit(1));
	}
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
		if (is_redirection_node(tree))
			ft_redirect(tree->redir, true);
		if (g_shell->should_continue_execution)
			ft_exec_builtin(cmd);
		return (0);
	}
	status = ft_exec_cmd(tree);
	if (is_pipe)
		exit(status);
	g_shell->last_exit_status = status;
	return (status);
}
