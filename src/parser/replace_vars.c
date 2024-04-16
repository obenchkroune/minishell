/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:20:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/16 07:26:48 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_name(char *str)
{
	char	*start;

	start = str;
	if (*str == '$')
		str++;
	if (*str == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit(*str++))
		return (ft_substr(start, 0, 2));
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (ft_substr(start, 0, str - start));
}

char	*replace_env_vars(char *arg, bool expand)
{
	char	*result;
	char	*name;
	char	*value;
	char	*replaced_str;

	result = ft_strdup(arg);
	if (!expand)
		return (result);
	while (*arg)
	{
		if (*arg == '$')
		{
			name = get_var_name(arg);
			value = get_env(name + 1);
			if (!value)
				value = "";
			replaced_str = ft_strreplace(result, name, value);
			arg += ft_strlen(name);
			(free(name), free(result));
			result = replaced_str;
			continue ;
		}
		arg++;
	}
	return (result);
}
