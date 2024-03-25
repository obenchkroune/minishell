/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:18:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/23 02:12:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *msg, char *cmd, ssize_t pos)
{
	ft_putstr_fd(RED "syntax error: " RESET, STDERR_FILENO);
	if (msg)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	if (cmd)
	{
		ft_putendl_fd(cmd, STDERR_FILENO);
		if (pos != -1)
		{
			while (pos--)
				ft_putstr_fd(RED "-" RESET, STDERR_FILENO);
			ft_putendl_fd(RED "^" RESET, STDERR_FILENO);
		}
	}
	exit(EXIT_FAILURE);
}

void	panic(char *msg)
{
	if (msg != NULL)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_empty(char *str)
{
	while (str && ft_isspace(*str))
		str++;
	return (ft_strlen(str) == 0);
}
