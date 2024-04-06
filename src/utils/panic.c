/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:59:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 04:59:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	panic(char *msg)
{
	perror(msg);
	cleanup_rotation();
	cleanup_shell();
	exit(EXIT_FAILURE);
}

void	panic_minishell(char *msg, int status)
{
	ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
	ft_fprintf(STDERR_FILENO, "%s\n", msg);
	cleanup_rotation();
	g_shell->last_exit_status = status;
}
