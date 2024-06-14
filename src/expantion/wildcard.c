/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:36:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_wildcard_args(t_list *args)
{
	t_list	*node;
	t_list	*files_list;
	char	*temp;

	node = args;
	while (node)
	{
		if (node->content && ft_strchr(node->content, '*')
			&& !ft_strchr(node->content, '"')
			&& !ft_strchr(node->content, '\''))
		{
			files_list = get_pattern_files(node->content);
			if (files_list)
			{
				ft_lstadd_back(&files_list, node->next);
				temp = node->content;
				node->content = files_list->content;
				node->next = files_list->next;
				(free(temp), free(files_list));
			}
		}
		node = node->next;
	}
}

char	*get_wildcard_pattern(char *arg)
{
	size_t	i;

	i = 0;
	while (!ft_strchr("<>|", arg[i]) && !ft_isspace(arg[i]))
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

t_list	*get_pattern_files(char *pattern)
{
	DIR				*dir;
	struct dirent	*entity;
	t_list			*result;

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
		ft_lstadd_back(&result, ft_lstnew(ft_strdup(entity->d_name)));
	}
	closedir(dir);
	return (result);
}

bool	check_wildcard(char *pattern, char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (true);
	if (*string == '\0')
	{
		if (ft_strcmp(pattern, "*") == 0)
			return (true);
		return (false);
	}
	if (*pattern == '*')
		return (check_wildcard(pattern, string + 1)
			|| check_wildcard(pattern + 1, string));
	if (*pattern == *string)
		return (check_wildcard(pattern + 1, string + 1));
	return (false);
}
