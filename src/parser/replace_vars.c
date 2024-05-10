/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:20:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 20:49:44 by obenchkr         ###   ########.fr       */
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
	if (ft_isdigit(*str))
		return (ft_substr(start, 0, 2));
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (ft_substr(start, 0, str - start));
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
	if (ft_strcmp(name, "$") == 0)
	{
		*arg += 1;
		return ;
	}
	*arg += ft_strlen(name);
	value = trim_whitespace(get_env(name + 1));
	if (!value)
		value = "";
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
