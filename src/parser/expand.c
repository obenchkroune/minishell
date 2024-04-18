/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:57:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/18 04:23:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_next_word(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && ft_strchr("\"'", str[i]))
		return (ft_substr(str, 1, ft_strchr(str + i + 1, str[i]) - str - 1));
	while (str[i] && !ft_strchr("'\"", str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

static size_t	get_len(t_arg *args)
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

char	*join_args(t_arg *args)
{
	t_arg	*node;
	size_t	len;
	char	*result;
	char	*content;

	node = args;
	while (node)
	{
		content = replace_env_vars(node->content, node->type);
		free(node->content);
		node->content = content;
		node = node->next;
	}
	len = get_len(args);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		panic("malloc");
	node = args;
	while (node)
	{
		ft_strlcat(result, node->content, len + 1);
		node = node->next;
	}
	return (result);
}

t_arg_type	get_arg_type(char c)
{
	if (c == '\'')
		return (ARG_SINGLE_QUOTE);
	if (c == '"')
		return (ARG_DOUBLE_QUOTE);
	return (ARG_PLAIN);
}

char	*expand_arg(const char *str)
{
	t_arg	*args_list;
	t_arg	*arg_node;
	size_t	i;
	char	*result;

	i = 0;
	args_list = NULL;
	while (str[i])
	{
		arg_node = create_arg_node(get_next_word(str + i), get_arg_type(str[i]));
		if (str[i] == '"' || str[i] == '\'')
		{
			add_arg_node(&args_list, arg_node);
			i += ft_strlen(arg_node->content) + 2;
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
