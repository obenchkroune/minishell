/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:32:42 by yaharkat          #+#    #+#             */
/*   Updated: 2024/06/16 14:26:53 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_all_n(char *s)
{
	while (*s)
	{
		if (*s != 'n')
			return (false);
		s++;
	}
	return (true);
}

void	ft_echo(t_cmd *cmd)
{
	bool	trim_nl;
	int		i;

	i = 1;
	trim_nl = false;
	if (cmd->argc >= 2 && !ft_strncmp(cmd->argv[1], "-n", 2)
		&& is_all_n(cmd->argv[1] + 1))
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
	set_status(0);
}
