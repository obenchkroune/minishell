/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 11:11:00 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in(t_redir *io, bool is_builtin)
{
	int		fd;
	char	*tmp;

	fd = open(io->file, O_RDONLY);
	if (fd == -1 && !is_builtin)
		panic(io->file);
	else if (fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": No such file or directory");
		panic_minishell(tmp, 1);
		free(tmp);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_out(t_redir *io, bool is_builtin)
{
	int		fd;
	char	*tmp;

	fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && !is_builtin)
		panic(io->file);
	else if (fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": Cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_append(t_redir *io, bool is_builtin)
{
	int		fd;
	char	*tmp;

	fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && !is_builtin)
		panic(io->file);
	else if (fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": Cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_heredoc(t_redir *io)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		panic("pipe");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, io->file) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	ft_redirect(t_redir *io, bool is_builtin)
{
	while (io && g_shell->should_continue_execution)
	{
		if (io->type == REDIR_IN)
			redirect_in(io, is_builtin);
		else if (io->type == REDIR_OUT)
			redirect_out(io, is_builtin);
		else if (io->type == REDIR_APPEND)
			redirect_append(io, is_builtin);
		else if (io->type == REDIR_HEREDOC)
			redirect_heredoc(io);
		io = io->next;
	}
	return (0);
}
