/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:53:46 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/07 11:04:31 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_terminal_attributes(void)
{
	if (tcgetattr(STDIN_FILENO, &g_shell->term) == -1)
	{
        perror("tcgetattr");
        return (-1);
    }
	g_shell->term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_shell->term) == -1)
	{
        perror("tcsetattr");
        return (-1);
    }
	return (0);
}
