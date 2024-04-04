/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 04:31:31 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in(t_io *io)
{
	int	fd;

	fd = open(io->file, O_RDONLY);
	if (fd == -1)
		panic("open");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_out(t_io *io)
{
	int	fd;

	fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		panic("open");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_append(t_io *io)
{
	int	fd;

	fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		panic("open");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_heredoc(t_io *io)
{
	int	fd;

	fd = open("to do", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		panic("open");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	ft_redirect(t_io *io)
{
	int	fd;

	while (io)
	{
		if (io->type == IO_IN)
			redirect_in(io);
		else if (io->type == IO_OUT)
			redirect_out(io);
		else if (io->type == IO_APPEND)
			redirect_append(io);
		else if (io->type == IO_HEREDOC)
			redirect_heredoc(io);
		io = io->next;
	}
	return (0);
}
