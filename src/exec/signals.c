/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/11 18:47:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signum)
{
	close(g_shell->secondary_input);
	set_status(signum + 128);
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	if (!g_shell->input)
	{
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
