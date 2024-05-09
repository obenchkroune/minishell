/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:25:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/09 01:14:31 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_heredoc(int signum)
{
	(void)signum;
	exit(1);
}

static int	get_heredoc_fd(char *delimer)
{
	int		pipe_fd[2];
	char	line[MAX_LINE_LENGTH];
	int		len;
	pid_t	pid;
	int		status;
	
	if (pipe(pipe_fd) == -1)
		panic("pipe");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			len = read(STDIN_FILENO, line, MAX_LINE_LENGTH - 1);
			if (len <= 0)
				break ;
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';
			if (!strncmp(line, delimer, len))
				break ;
			write(pipe_fd[1], line, strlen(line));
			write(pipe_fd[1], "\n", 1);
		}
		exit(0);
	}
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
