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

typedef struct s_arg
{
	char			*content;
	bool			expand;
	struct	s_arg	*next;
}	t_arg;

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

t_arg	*create_arg_node(char *value, bool expand)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		panic("malloc");
	ft_bzero(arg, sizeof(t_arg));
	arg->content = value;
	arg->expand = expand;
	return (arg);
}

void	cleanup_arg_nodes(t_arg *args)
{
	if (!args)
		return ;
	cleanup_arg_nodes(args->next);
	free(args->content);
	free(args);
}

void	add_arg_node(t_arg **root, t_arg *arg)
{
	t_arg	*tail;

	if (!root || !arg)
		return ;
	if (*root == NULL)
	{
		*root = arg;
		return ;
	}
	tail = *root;
	while (tail->next)
		tail = tail->next;
	tail->next = arg;
}

char	*get_next_word(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		return (ft_substr(str, 1, ft_strchr(str + i + 1, str[i]) - str - 1));
	while (str[i] && !ft_strchr("'\"", str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

size_t	get_len(t_arg *args)
{
	size_t	len;

	len = 0;
	while (args)
	{
		len += ft_strlen(args->content);
		args = args->next;
	}
	return (len);
}

char	*replace_env_vars(char *arg)
{
	char	*result;
	char	*name;
	char	*value;
	char	*new_result;
	size_t	i;

	result = ft_strdup(arg);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
		{
			name = get_var_name(result + i);
			value = get_env(name + 1);
			if (!value)
				value = "";
			new_result = ft_strreplace(result, name, value);
			free(result);
			result = new_result;
			i += ft_strlen(value) - 1;
			free(name);
		}
		else
			i++;
	}
	return (result);
}

char	*join_args(t_arg *args)
{
	t_arg	*temp;
	size_t	len;
	char	*result;
	char	*content;

	temp = args;
	while (temp)
	{
		if (temp->expand)
			content = replace_env_vars(temp->content);
		else
			content = ft_strdup(temp->content);
		free(temp->content);
		temp->content = content;
		temp = temp->next;
	}
	len = get_len(args);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		panic("malloc");
	temp = args;
	while (temp)
	{
		ft_strlcat(result, temp->content, len + 1);
		temp = temp->next;
	}
	return (result);
}

static char	*expand_arg(const char *str)
{
	t_arg	*args_list;
	t_arg	*arg_node;
	size_t	i;
	char	*result;

	i = 0;
	args_list = NULL;
	while (str[i])
	{
		arg_node = create_arg_node(get_next_word(str + i), str[i] != '\'');
		if (str[i] == '"' || str[i] == '\'')
		{
			add_arg_node(&args_list, arg_node);
			i += ft_strlen(arg_node->content) + 1;
		}
		else
		{
			add_arg_node(&args_list, arg_node);
			i += ft_strlen(arg_node->content);
		}
	}
	result = join_args(args_list);
	cleanup_arg_nodes(args_list);
	return (result);
}

char	**expand_argv(char **argv)
{
	char	*arg;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		arg = expand_arg(argv[i]);
		free(argv[i]);
		argv[i] = arg;
		i++;
	}
	return (argv);
}
