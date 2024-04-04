/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 03:49:16 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirect(t_io *io)
{
	int	fd;

	while (io)
	{
		if (io->type == IO_IN)
		{
			fd = open(io->file, O_RDONLY);
			if (fd == -1)
				panic("open");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (io->type == IO_OUT)
		{
			fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				panic("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (io->type == IO_APPEND)
		{
			fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				panic("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (io->type == IO_HEREDOC)
		{
			fd = 0;
			// open a file to read the heredoc content
			// fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				panic("open");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		io = io->next;
	}
	return (0);
}
