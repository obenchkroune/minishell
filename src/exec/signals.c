/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/08 00:22:39 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	ft_fprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	if (!g_shell->input)
		rl_on_new_line();
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
