/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:18:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 04:48:19 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *msg, char *cmd, size_t pos)
{
	if (msg)
	{
		ft_putstr_fd(RED "syntax error: " RESET, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	ft_putendl_fd(cmd, STDERR_FILENO);
	while (pos--)
		ft_putstr_fd(RED "-" RESET, STDERR_FILENO);
	ft_putendl_fd(RED "^" RESET, STDERR_FILENO);
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
