/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:18:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/05 05:55:54 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}

void	panic(char *msg)
{
	perror(msg);
	cleanup_rotation();
	cleanup_shell();
	exit(EXIT_FAILURE);
}

void	panic_minishell(char *msg, int status)
{
	ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
	ft_fprintf(STDERR_FILENO, "%s\n", msg);
	cleanup_rotation();
	g_shell->last_exit_status = status;
}
int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_empty(char *str)
{
	if (!str)
		ft_exit();
	while (*str && ft_isspace(*str))
		str++;
	return (ft_strlen(str) == 0);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
