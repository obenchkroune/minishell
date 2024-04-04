/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:32:42 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 02:43:00 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
{
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
	{
		n_flag = true;
		i++;
	}
	while (args && args[i])
	{
		ft_fprintf(STDIN_FILENO, "%s ", args[i]);
		i++;
	}
	if (n_flag == false)
		ft_fprintf(STDIN_FILENO, "\n");
}
