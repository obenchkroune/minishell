/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:25:32 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/31 18:33:32 by yaharkat         ###   ########.fr       */
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

static int	ft_exec_pipeline(t_node *tree)
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
			return (ft_get_exit_status(status));
		}
	}
	return (0);
}

int	ft_exec_node(t_node *tree, bool piped)
{
	int	status;

	if (!tree)
		return (1);
	if (tree->type == N_PIPE)
		return (ft_exec_pipeline(tree));
	else if (tree->type == N_CMD)
		return (ft_exec_simple_cmd(tree, piped));
	return (0);
}
