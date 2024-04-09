/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:03:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/09 01:48:55 by yaharkat         ###   ########.fr       */
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
	g_shell->has_syntax_error = false;
	g_shell->has_heredoc = false;
	g_shell->has_unclosed_pipe = false;
	g_shell->inside_unclosed_pipe = false;
	g_shell->should_continue_execution = true;
}
