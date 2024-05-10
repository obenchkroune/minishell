/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:25:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 18:07:29 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_sigint_handler(int signum)
{
	(void)signum;
	exit(1);
}

void	heredoc_fork(int fd, char *delimer)
{
	char	*line;

	signal(SIGINT, child_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimer) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	exit(0);
}

void	get_heredoc_filename(char name_ptr[15])
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		panic("open");
	ft_bzero(name_ptr, 15);
	ft_strlcat(name_ptr, "/tmp/", 15);
	read(fd, name_ptr + 5, 8);
	close(fd);
}

static int	get_heredoc_fd(t_redir *redir)
{
	pid_t	pid;
	int		status;
	int		fd;

	get_heredoc_filename(redir->heredoc_file);
	unlink(redir->heredoc_file);
	fd = open(redir->heredoc_file, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		panic("open");
	pid = fork();
	if (pid == 0)
		heredoc_fork(fd, redir->file);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		g_shell->has_syntax_error = true;
	close(fd);
	return (open(redir->heredoc_file, O_RDONLY));
}

int	get_redir_fd(t_redir *redir)
{
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	else if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (redir->type == REDIR_HEREDOC)
		return (get_heredoc_fd(redir));
	return (-1);
}
