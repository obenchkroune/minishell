/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 19:23:35 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_hostname(void)
{
	if (get_env("HOSTNAME"))
		return (ft_strdup(get_env("HOSTNAME")));
	else if (get_env("HOST"))
		return (ft_strdup(get_env("HOST")));
	return (ft_strdup("42"));
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
	set_env("PWD", g_shell->cwd);
	g_shell->has_syntax_error = false;
	g_shell->has_heredoc = false;
	g_shell->has_unclosed_pipe = false;
	g_shell->inside_unclosed_pipe = false;
	g_shell->should_continue_execution = true;
	g_shell->username = get_username();
	g_shell->hostname = get_hostname();
}
