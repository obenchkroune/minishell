/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:25:32 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/18 13:19:59 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_pipe_child(t_node *node, int pipe[2], int direction)
{
	int	status;

	if (direction == DIR_LEFT)
	{
		close(pipe[0]);
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
	}
	else if (direction == DIR_RIGHT)
	{
		close(pipe[1]);
		dup2(pipe[0], STDIN_FILENO);
		close(pipe[0]);
	}
	status = ft_exec_node(node, true);
	exit(status);
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	ft_exec_pipeline(t_node *tree)
{
	int	status;
	int	pipe_fd[2];
	int	pid_l;
	int	pid_r;

	pipe(pipe_fd);
	pid_l = fork();
	if (!pid_l)
		ft_exec_pipe_child(tree->left, pipe_fd, DIR_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			ft_exec_pipe_child(tree->right, pipe_fd, DIR_RIGHT);
		else
		{
			(close(pipe_fd[0]), close(pipe_fd[1]), waitpid(pid_l, &status, 0),
				waitpid(pid_r, &status, 0));
			set_status(ft_get_exit_status(status));
			return (ft_get_exit_status(status));
		}
	}
	return (0);
}

int	ft_exec_subshell(t_node *tree)
{
	t_env	*env_dup;
	int		status;

	env_dup = ft_dup_env();
	status = ft_exec_node(tree->left, false);
	free_env();
	g_shell->env = env_dup;
	update_envp();
	return (status);
}

int	ft_exec_node(t_node *tree, bool is_pipe)
{
	if (!tree || g_shell->has_syntax_error)
		return (1);
	if (tree->type == N_SUBSHELL)
		return (ft_exec_subshell(tree));
	if (tree->type == N_SEMICOL)
		return (ft_exec_node(tree->left, false),
			ft_exec_node(tree->right, false));
	if (tree->type == N_AND && ft_exec_node(tree->left, false) == 0)
		return (ft_exec_node(tree->right, false));
	if (tree->type == N_OR && ft_exec_node(tree->left, false) != 0)
		return (ft_exec_node(tree->right, false));
	if (tree->type == N_PIPE)
		return (ft_exec_pipeline(tree));
	else if (tree->type == N_CMD)
		return (ft_exec_simple_cmd(tree, is_pipe));
	return (0);
}
