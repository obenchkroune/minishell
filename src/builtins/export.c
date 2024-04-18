/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/18 12:57:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (equal_sign)
		{
			key = ft_substr(cmd->argv[i], 0, equal_sign - cmd->argv[i]);
			set_env(key, equal_sign + 1);
			free(key);
			key = NULL;
		}
		i++;
	}
}
