/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **envp)
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
}
