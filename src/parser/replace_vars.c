/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:20:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/11 18:57:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit(str[i]))
		return (ft_substr(str, 0, 2));
	while (str[i] && (ft_isalnum(str[i]) || *str == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

static void	expand_home(char **result)
{
	char	*replaced_str;

	replaced_str = ft_strreplace(*result, "~", getenv("HOME"));
	free(*result);
	*result = replaced_str;
}

static void	expand_env_var(char **result, char **arg)
{
	char	*name;
	char	*value;
	char	*replaced_str;

	name = get_var_name(*arg);
	if (ft_strlen(name) == 1)
	{
		*arg += 1;
		return ;
	}
	*arg += ft_strlen(name);
	value = trim_whitespace(get_env(name + 1));
	if (!value)
		value = ft_strdup("");
	replaced_str = ft_strreplace(*result, name, value);
	(free(name), free(*result), free(value));
	*result = replaced_str;
}

char	*replace_env_vars(char *arg, t_arg_type type)
{
	char	*result;

	result = ft_strdup(arg);
	if (type == ARG_SINGLE_QUOTE)
		return (result);
	while (*arg)
	{
		if (type == ARG_PLAIN && *arg == '~' && ft_strchr("/ ", *(arg + 1)))
			(expand_home(&result), arg++);
		else if (*arg == '$')
		{
			expand_env_var(&result, &arg);
			continue ;
		}
		else if (type == ARG_PLAIN && ft_strchr(arg, '*'))
			expand_wildcard(&result, &arg);
		else
			arg++;
	}
	return (result);
}
