/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:20:09 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 17:02:55 by obenchkr         ###   ########.fr       */
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
	value = get_env(name + 1);
	if (!value)
		value = "";
	replaced_str = ft_strreplace(*result, name, value);
	(free(name), free(*result));
	*result = replaced_str;
}

char	*get_wildcard_pattern(char *arg)
{
	size_t	i;

	i = 0;
	while (!ft_strchr("<>| ", arg[i]))
	{
		i++;
	}
	return (ft_substr(arg, 0, i));
}

char	*add_file_to_string(char *dst, char *file)
{
	char	*result;
	char	*temp;
	
	if (dst == NULL)
		return (ft_strdup(file));
	result = ft_strjoin(dst, " ");
	temp = result;
	result = ft_strjoin(result, file);
	free(temp);
	return (result);
}

char	*get_pattern_files(char *pattern)
{
	DIR				*dir;
	struct dirent	*entity;
	char			*result;
	char			*temp;

	result = NULL;
	dir = opendir(".");
	if (!dir)
		panic("opendir");
	while (1)
	{
		entity = readdir(dir);
		if (!entity)
			break ;
		if (!ft_strcmp(entity->d_name, ".") || !ft_strcmp(entity->d_name, "..")
			|| !check_wildcard(pattern, entity->d_name)
			|| (entity->d_name[0] == '.' && !ft_strchr(pattern, '.')))
			continue ;
		temp = result;
		result = add_file_to_string(result, entity->d_name);
		free(temp);
	}
	closedir(dir);
	return (result);
}

static void	expand_wildcard(char **result, char **arg)
{
	char	*pattern;
	char	*value;
	char	*replaced_str;

	pattern = get_wildcard_pattern(*arg);
	*arg += ft_strlen(pattern);
	value = get_pattern_files(pattern);
	if (!value)
	{
		free(pattern);
		return ;
	}
	replaced_str = ft_strreplace(*result, pattern, value);
	(free(pattern), free(*result), free(value));
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
