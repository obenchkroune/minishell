/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:30:04 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/05 05:38:11 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(void)
{
	int	status;

	status = g_shell->last_exit_status;
	cleanup_rotation();
	cleanup_shell();
	exit(status);
}
