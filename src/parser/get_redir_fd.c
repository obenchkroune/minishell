/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:25:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/13 15:55:31 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_heredoc(int fd, char *delimer)
{
	char	*line;
	char	*temp;

	while (g_shell->secondary_input != -1)
	{
		write(1, "> ", 2);
		line = get_next_line(g_shell->secondary_input);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		if (!line || ft_strcmp(line, delimer) == 0)
		{
			free(line);
			break ;
		}
		temp = line;
		line = ft_expand(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		(free(line), free(temp));
	}
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
	int		fd;

	get_heredoc_filename(redir->heredoc_file);
	unlink(redir->heredoc_file);
	fd = open(redir->heredoc_file, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		panic("open");
	read_heredoc(fd, redir->file);
	close(fd);
	return (open(redir->heredoc_file, O_RDONLY));
}

int	get_redir_fd(t_redir *redir)
{
	char	*temp;

	if (redir->type != REDIR_HEREDOC)
	{
		temp = redir->file;
		redir->file = ft_expand(redir->file);
		free(temp);
	}
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
