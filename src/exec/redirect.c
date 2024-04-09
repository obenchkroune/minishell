/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 03:40:45 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/09 02:00:49 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_in(t_redir *io, bool is_builtin)
{
	int	fd;

	fd = open(io->file, O_RDONLY);
	if (fd == -1 && !is_builtin)
		panic("open");
	else if (fd == -1 && is_builtin)
	{
		panic_minishell("No such file or directory", 1);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_out(t_redir *io, bool is_builtin)
{
	int	fd;

	fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && !is_builtin)
		panic("open");
	else if (fd == -1 && is_builtin)
	{
		panic_minishell("Cannot create file", 1);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_append(t_redir *io, bool is_builtin)
{
	int	fd;

	fd = open(io->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && !is_builtin)
		panic("open");
	else if (fd == -1 && is_builtin)
	{
		panic_minishell("Cannot create file", 1);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	redirect_heredoc(t_redir *io, bool is_builtin)
{
	int	fd;

	fd = open(io->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && !is_builtin)
		panic("open");
	else if (fd == -1 && is_builtin)
	{
		panic_minishell("No such file or directory", 1);
		g_shell->should_continue_execution = false;
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
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
			redirect_heredoc(io, is_builtin);
		io = io->next;
	}
	return (0);
}
