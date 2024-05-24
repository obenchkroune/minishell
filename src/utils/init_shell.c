/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/24 03:23:25 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_process_id(void)
{
	char	*result;
	int		fd;
	int		bytes;
	char	buffer[20];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (ft_strdup("0"));
	bytes = read(fd, buffer, 19);
	if (bytes == -1)
		panic("read");
	buffer[bytes] = '\0';
	result = ft_itoa(ft_atoi(buffer));
	close(fd);
	return (result);
}

void	init_shell(char **av, char **envp)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		panic("malloc");
	ft_bzero(g_shell, sizeof(t_shell));
	set_terminal_attributes();
	g_shell->env = parse_env(envp);
	update_envp();
	g_shell->cwd = getcwd(NULL, 0);
	set_env("PWD", g_shell->cwd);
	set_env("OLDPWD", g_shell->cwd);
	g_shell->has_syntax_error = false;
	g_shell->has_heredoc = false;
	g_shell->secondary_input = -1;
	set_status(0);
	g_shell->home = ft_strdup(get_env("HOME"));
	g_shell->process_id = get_process_id();
	g_shell->shell_script = av[0];
}
