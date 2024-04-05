/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:32:42 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/05 07:12:22 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = true;
		i++;
	}
	while (args && args[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s", args[i]);
		i++;
	}
	if (n_flag == false)
		ft_fprintf(STDOUT_FILENO, "\n");
}
