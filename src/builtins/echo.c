/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:32:42 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/05 21:38:09 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	bool	trim_nl;
	int		i;

	i = 1;
	trim_nl = false;
	if (cmd->argc >= 2 && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		trim_nl = true;
		i++;
	}
	while (i < cmd->argc)
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!trim_nl)
		ft_fprintf(STDOUT_FILENO, "\n");
}
