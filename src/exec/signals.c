/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 06:45:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/05 07:46:49 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	ft_fprintf(STDOUT_FILENO, "\n");
	ft_fprintf(STDOUT_FILENO, "%s", g_shell->prompt);
}

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
	// cleanup_rotation();
	// cleanup_shell();
	// exit(g_shell->last_exit_status);
}

void	signal_init(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		panic("signal");
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		panic("signal");
}
