/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/07 21:53:51 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_in(t_redir *io, bool is_builtin)
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
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redirect_out(t_redir *io, bool is_builtin)
{
	int		fd;
	char	*tmp;

	fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && !is_builtin)
		panic(io->file);
	else if (fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redirect_append(t_redir *io, bool is_builtin)
{
	int		fd;
	char	*tmp;

	fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && !is_builtin)
		panic(io->file);
	else if (fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void	redirect_heredoc(t_redir *io)
{
	int		pipe_fd[2];
	char	line[MAX_LINE_LENGTH];
	int		len;

	if (pipe(pipe_fd) == -1)
		panic("pipe");
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		len = read(STDIN_FILENO, line, MAX_LINE_LENGTH - 1);
		if (len <= 0)
			break ;
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!strncmp(line, io->file, len))
			break ;
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		panic("dup2");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	ft_redirect(t_redir *redir, bool is_builtin)
{
	expand_redir(redir);
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (redirect_in(redir, is_builtin))
				return (1);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (redirect_out(redir, is_builtin))
				return (1);
		}
		else if (redir->type == REDIR_APPEND)
		{
			if (redirect_append(redir, is_builtin))
				return (1);
		}
		else if (redir->type == REDIR_HEREDOC)
			redirect_heredoc(redir);
		redir = redir->next;
	}
	return (0);
}
