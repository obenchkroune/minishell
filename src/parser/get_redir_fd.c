/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:25:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 02:55:42 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_heredoc(int signum)
{
	(void)signum;
	exit(1);
}

void	heredoc_fork(int pipe_fd[2], char *delimer)
{
	char	*line;

	signal(SIGINT, sigint_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimer) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	exit(0);
}

static int	get_heredoc_fd(char *delimer)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		panic("pipe");
	pid = fork();
	if (pid == 0)
		heredoc_fork(pipe_fd, delimer);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		g_shell->has_syntax_error = true;
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_redir_fd(char *name, t_redir_type type)
{
	if (type == REDIR_APPEND)
		return (open(name, O_CREAT | O_APPEND | O_WRONLY, 0644));
	else if (type == REDIR_IN)
		return (open(name, O_RDONLY));
	else if (type == REDIR_OUT)
		return (open(name, O_CREAT | O_TRUNC | O_WRONLY));
	else if (type == REDIR_HEREDOC)
		return (get_heredoc_fd(name));
	return (-1);
}
