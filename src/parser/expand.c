/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:57:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/09 01:00:10 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strreplace(char *str, char *find, char *replace)
{
	char	*result;
	size_t	len;
	char	*find_pos;

	if (!str || !find || !replace)
		return (NULL);
	find_pos = ft_strnstr(str, find, ft_strlen(str));
	if (!find_pos)
		return (ft_strdup(str));
	len = ft_strlen(str) - ft_strlen(find) + ft_strlen(replace);
	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		panic("malloc");
	ft_strlcat(result, str, find_pos - str + 1);
	ft_strlcat(result, replace, len + 1);
	ft_strlcat(result, find_pos + ft_strlen(find), len + 1);
	return (result);
}

static char	*get_var_name(char *str)
{
	char	*start;

	start = str++;
	if (*str == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit(*str++))
		return (ft_substr(start, 0, 2));
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (ft_substr(start, 0, str - start));
}

static char	*expand_arg(char *arg)
{
	char	*result;
	char	*name;
	char	*value;
	char	*temp;

	result = ft_strtrim(arg, "\"");
	while (*arg)
	{
		if (*arg == '$')
		{
			name = get_var_name(arg);
			value = get_env(name + 1);
			if (!value)
				value = "";
			temp = result;
			result = ft_strreplace(result, name, value);
			arg += ft_strlen(name);
			free(temp);
			free(name);
			continue ;
		}
		arg++;
	}
	return (result);
}

char	**expand_argv(char **argv)
{
	char	*arg;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\'')
			arg = expand_arg(argv[i]);
		else
			arg = ft_strtrim(argv[i], "'");
		free(argv[i]);
		argv[i++] = arg;
	}
	return (argv);
}
