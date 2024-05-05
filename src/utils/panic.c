/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/05 21:46:02 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	panic(char *msg)
{
	ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
	perror(msg);
	cleanup_rotation();
	cleanup_shell();
	exit(EXIT_FAILURE);
}

void	panic_minishell(char *msg, int status)
{
	ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
	ft_fprintf(STDERR_FILENO, "%s\n", msg);
	g_shell->last_exit_status = status;
}
