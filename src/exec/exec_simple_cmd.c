/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:52:43 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 02:50:19 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	ft_redirect(t_io *io)
// {
// 	int	fd;

// 	if (io->type == IO_IN)
// 	{
// 		fd = open(io->file, O_RDONLY);
// 		if (fd == -1)
// 			panic("open");
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	else if (io->type == IO_OUT)
// 	{
// 		fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 			panic("open");
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	else if (io->type == IO_APPEND)
// 	{
// 		fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 			panic("open");
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	else if (io->type == IO_HEREDOC)
// 	{
// 		fd = 0;
// 		// open a file to read the heredoc content
// 		// fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 			panic("open");
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	return (0);
// }

static int	ft_exec_cmd(t_node *tree, char **args, bool piped)
{
	int		status;
	pid_t	pid;
	t_cmd	*cmd;

	(void)piped;
	cmd = tree->cmd;
	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		// if (tree->io->type == IO_IN || tree->io->type == IO_OUT
		// 	|| tree->io->type == IO_APPEND || tree->io->type == IO_HEREDOC)
		// 	ft_redirect(tree->io);
		if (execve(cmd->path, args, env_tab(g_shell->env)) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_exec_simple_cmd(t_node *tree, bool piped)
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
	status = ft_exec_cmd(tree, args, piped);
	return (status);
}
