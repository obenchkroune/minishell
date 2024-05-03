/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/03 18:51:15 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signum)
{
	g_shell->last_exit_status = signum + 128;
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	if (!g_shell->input || g_shell->has_heredoc)
	{
		rl_on_new_line();
		rl_redisplay();
		g_shell->has_heredoc = false;
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	signal_init(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGQUIT,
			sigquit_handler) == SIG_ERR)
		panic("signal");
}
