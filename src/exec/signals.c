/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/16 04:52:35 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signum)
{
	printf("\n\r%s", g_shell->prompt);
	g_shell->last_exit_status = signum + 128;
	rl_replace_line("", 0);
	if (!g_shell->input)
	{
		rl_on_new_line();
	}
	if (!g_shell->inside_unclosed_pipe)
		rl_redisplay();
	else
		ft_fprintf(STDOUT_FILENO, ">");
}

void	sigquit_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	signal_init(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		panic("signal");
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		panic("signal");
}
