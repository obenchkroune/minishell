/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:18:49 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 04:50:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_error(t_token token)
{
	g_shell->has_syntax_error = true;
	ft_fprintf(2, "minishell: syntax error near unexpected token: '%s'\n", token.value);
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
	{
		printf("exit\n");
		ft_exit();
	}
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
