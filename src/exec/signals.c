/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/07 21:15:52 by yaharkat         ###   ########.fr       */
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
		g_shell->has_heredoc = false;
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_init(void)
{
	struct sigaction	quit_action;

	ft_bzero(&quit_action, sizeof(sigaction));
	quit_action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &quit_action, NULL) != 0)
		panic("sigaction");
	if (signal(SIGINT, &sigint_handler) != 0)
		panic("signal");
}
