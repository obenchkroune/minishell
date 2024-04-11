/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/11 18:13:11 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_hostname(void)
{
	int		fd;
	char	*result;
	char	*line;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("42"));
	line = get_next_line(fd);
	result = ft_strtrim(line, "\n");
	free(line);
	close(fd);
	return (result);
}

static char	*get_username(void)
{
	char	*username;

	username = get_env("USER");
	if (!username)
		return (ft_strdup("minishell"));
	return (ft_strdup(username));
}

void	init_shell(char **envp)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		panic("malloc");
	ft_bzero(g_shell, sizeof(t_shell));
	set_terminal_attributes();
	g_shell->envp = parse_env(envp);
	g_shell->cwd = getcwd(NULL, 0);
	g_shell->has_syntax_error = false;
	g_shell->has_heredoc = false;
	g_shell->has_unclosed_pipe = false;
	g_shell->inside_unclosed_pipe = false;
	g_shell->should_continue_execution = true;
	g_shell->username = get_username();
	g_shell->hostname = get_hostname();
}
