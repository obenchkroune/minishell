/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:30:04 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 05:59:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;

	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_cmd *cmd)
{
	if (cmd->argc > 2)
	{
		panic_minishell("exit: too many arguments",	1);
		return ;
	}
	if (cmd->argc == 2)
	{
		if (!ft_isnumber(cmd->argv[1]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				cmd->argv[1]);
			exit(255);
		}
		cleanup_rotation();
		cleanup_shell();
		printf("exit\n");
		exit(ft_atoi(cmd->argv[1]));
	}
	exit(g_shell->last_exit_status);
}
