/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:06:24 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/06 03:26:11 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_export(char **args)
{
	char	*equal_sign;
	char	*key;

	if (ft_tabsize(args) == 1)
	{
		ft_env();
		return ;
	}
	while (args && *args)
	{
		equal_sign = ft_strchr(*args, '=');
		if (equal_sign)
		{
			key = ft_substr(*args, 0, equal_sign - *args);
			set_env(key, equal_sign + 1);
			free(key);
			key = NULL;
		}
		args++;
	}
}
