/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/19 19:29:24 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_valid_name(char *name)
{
	if (!ft_isalpha(*name))
		return (false);
	while (*++name)
	{
		if (!ft_isalnum(*name))
			return (false);
	}
	return (true);
}

void	ft_export(t_cmd *cmd)
{
	char	*equal_sign;
	char	*key;
	int		i;

	if (cmd->argc == 1)
	{
		ft_env();
		return ;
	}
	i = 1;
	while (i < cmd->argc)
	{
		equal_sign = ft_strchr(cmd->argv[i], '=');
		if (!equal_sign || equal_sign - cmd->argv[i] == 0)
			key = ft_strdup(cmd->argv[i]);
		else
			key = ft_substr(cmd->argv[i], 0, equal_sign - cmd->argv[i]);
		if (!is_valid_name(key))
		{
			ft_fprintf(2, "minishell: export: `%s' not a valid identifier\n",
				key);
			g_shell->last_exit_status = 1;
			(free(key), i++);
			continue ;
		}
		set_env(key, equal_sign + 1);
		free(key);
		key = NULL;
		i++;
	}
}
