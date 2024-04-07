/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/07 02:45:56 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirection_node(t_node *tree)
{
	return (tree->redir && (tree->redir->type == REDIR_IN || tree->redir->type == REDIR_OUT
			|| tree->redir->type == REDIR_APPEND || tree->redir->type == REDIR_HEREDOC));
}

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
		if (is_redirection_node(tree))
			ft_redirect(tree->redir);
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
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	ft_exec_simple_cmd(t_node *tree, bool is_pipe)
{
	int		status;
	char	**args;
	t_cmd	*cmd;

	cmd = tree->cmd;
	args = expand_argv(cmd->argv);
	if (ft_is_builtin(cmd->argv[0]))
	{
		ft_exec_builtin(args);
		return (0);
	}
	status = ft_exec_cmd(tree, args);
	if (is_pipe)
		exit(status);
	g_shell->last_exit_status = status;
	return (status);
}
