/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:20:47 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 14:21:19 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_next_word(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && ft_strchr("\"'", str[i]))
		return (ft_substr(str, 1, ft_strchr(str + i + 1, str[i]) - str - 1));
	while (str[i] && !ft_strchr("'\"", str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

t_arg_type	get_arg_type(char c)
{
	if (c == '\'')
		return (ARG_SINGLE_QUOTE);
	if (c == '"')
		return (ARG_DOUBLE_QUOTE);
	return (ARG_PLAIN);
}

char	*ft_expand(const char *str)
{
	t_arg	*args_list;
	t_arg	*arg_node;
	size_t	i;
	char	*result;

	i = 0;
	args_list = NULL;
	while (str[i])
	{
		arg_node = create_arg_node(get_next_word(str + i),
				get_arg_type(str[i]));
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
	return (cleanup_arg_nodes(args_list), result);
}
