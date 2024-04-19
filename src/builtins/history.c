/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 02:42:05 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 16:48:01 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_history(void)
{
	t_history	*tmp;
	t_history	*next;

	tmp = g_shell->history;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	g_shell->history = NULL;
	rl_clear_history();
}

void	set_history(char *line)
{
	t_history	*new;
	t_history	*tmp;

	new = malloc(sizeof(t_history));
	if (!new || ft_strnstr(line, "history", ft_strlen(line)))
	{
		if (new)
			free(new);
		return ;
	}
	new->value = ft_strdup(line);
	new->next = NULL;
	if (!g_shell->history)
		g_shell->history = new;
	else
	{
		tmp = g_shell->history;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_history(t_cmd *cmd)
{
	t_history	*tmp;
	int			i;

	if (cmd->argc > 2)
	{
		panic_minishell("minishell: history: too many arguments\n", 2);
		return ;
	}
	if (cmd->argc == 2 && !ft_strcmp(cmd->argv[1], "-c"))
	{
		ft_clear_history();
		return ;
	}
	i = 1;
	tmp = g_shell->history;
	while (tmp)
	{
		printf("%d %s\n", i, tmp->value);
		tmp = tmp->next;
		i++;
	}
}
