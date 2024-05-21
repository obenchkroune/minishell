/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:30:04 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	status;

	status = g_shell->last_exit.status;
	if (cmd->argc > 2)
	{
		panic_minishell("exit: too many arguments", 1);
		return ;
	}
	if (cmd->argc == 2)
	{
		if (!ft_isnumber(cmd->argv[1]))
		{
			ft_fprintf(STDERR_FILENO,
				"exit\nminishell: exit: %s: numeric argument required\n",
				cmd->argv[1]);
			exit(2);
		}
		status = ft_atoi(cmd->argv[1]);
	}
	cleanup_rotation();
	cleanup_shell();
	printf("exit\n");
	exit(status);
}
