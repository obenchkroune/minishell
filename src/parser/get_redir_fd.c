/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:25:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/16 11:57:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(t_redir *redir)
{
	char	*line;
	char	*temp;
	int		fd[2];

	if (pipe(fd) < 0)
		panic("pipe");
	while (g_shell->secondary_input != -1)
	{
		write(1, "> ", 2);
		line = get_next_line(g_shell->secondary_input);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		if (!line || ft_strcmp(line, redir->file) == 0)
			return (close(fd[1]), free(line), fd[0]);
		temp = line;
		line = ft_expand(line, true);
		(write(fd[1], line, ft_strlen(line)), write(fd[1], "\n", 1));
		(free(line), free(temp));
	}
	close(fd[1]);
	return (fd[0]);
}

int	get_redir_fd(t_redir *redir)
{
	char	*temp;

	if (redir->file)
	{
		temp = redir->file;
		redir->file = ft_expand(redir->file, redir->type != REDIR_HEREDOC);
		free(temp);
	}
	if (redir->type == REDIR_APPEND)
		return (open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	else if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (redir->type == REDIR_HEREDOC)
		return (read_heredoc(redir));
	return (-1);
}
