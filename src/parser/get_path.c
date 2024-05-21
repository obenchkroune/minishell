/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 03:11:20 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 05:41:18 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	useless_fn(void *ptr)
{
	(void)ptr;
}

char	**get_path(void)
{
	t_list	*path_lst;
	char	*str;
	char	**result;
	char	*start;

	path_lst = NULL;
	str = get_env("PATH");
	start = str;
	while (str && *str++)
	{
		if (*str == ':')
		{
			if (ft_strchr(":", *(str + 1)) || str == start)
				ft_lstadd_back(&path_lst, ft_lstnew(ft_strdup(".")));
			else
				ft_lstadd_back(&path_lst, ft_lstnew(
						ft_substr(start, 0, str - start)));
			start = str + 1;
		}
	}
	result = ft_lsttab(path_lst);
	ft_lstclear(&path_lst, &useless_fn);
	return (result);
}
