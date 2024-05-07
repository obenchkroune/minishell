/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/07 21:16:41 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	g_shell->last_exit_status = 0;
}
