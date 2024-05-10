/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:56:59 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 10:04:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
    set the shell's last exit status
*/
void    set_status(int status)
{
    g_shell->last_exit.status = status;
    free(g_shell->last_exit.str);
    g_shell->last_exit.str = ft_itoa(g_shell->last_exit.status);
}
