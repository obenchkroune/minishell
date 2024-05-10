/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:28:40 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 16:16:40 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
