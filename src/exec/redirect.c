/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/21 05:39:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in(t_redir *io, bool is_builtin)
{
	char	*tmp;

	if (io->fd == -1 && !is_builtin)
		panic(io->file);
	else if (io->fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": No such file or directory");
		panic_minishell(tmp, 1);
		free(tmp);
		return (1);
	}
	dup2(io->fd, STDIN_FILENO);
	close(io->fd);
	return (0);
}

static int	redirect_out(t_redir *io, bool is_builtin)
{
	char	*tmp;

	if (io->fd == -1 && !is_builtin)
		panic(io->file);
	else if (io->fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		return (1);
	}
	dup2(io->fd, STDOUT_FILENO);
	close(io->fd);
	return (0);
}

static int	redirect_append(t_redir *io, bool is_builtin)
{
	char	*tmp;

	if (io->fd == -1 && !is_builtin)
		panic(io->file);
	else if (io->fd == -1 && is_builtin)
	{
		tmp = ft_strjoin(io->file, ": cannot create file");
		panic_minishell(tmp, 1);
		free(tmp);
		return (1);
	}
	dup2(io->fd, STDOUT_FILENO);
	close(io->fd);
	return (0);
}

static void	redirect_heredoc(t_redir *io)
{
	if (dup2(io->fd, STDIN_FILENO) == -1)
		panic("dup2");
}

int	ft_redirect(t_redir *redir, bool is_builtin)
{
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
