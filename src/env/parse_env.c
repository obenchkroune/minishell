/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:27:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 11:42:26 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*parse_env(char **envp)
{
	t_env	*result;
	char	*name;
	char	*eq_sign;

	result = NULL;
	while (*envp)
	{
		eq_sign = ft_strchr(*envp, '=');
		if (!eq_sign)
			add_env(&result, *envp, "");
		else
		{
			name = ft_substr(*envp, 0, eq_sign - *envp);
			if (!name)
				panic("malloc");
			add_env(&result, name, eq_sign + 1);
			free(name);
		}
		envp++;
	}
	return (result);
}
