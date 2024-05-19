/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/19 07:56:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "libft.h"

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
		return (false);
	if (*pattern == '*')
		return (check_wildcard(pattern, ++string)
			|| check_wildcard(++pattern, string));
	if (*pattern == *string)
		return (check_wildcard(++pattern, ++string));
	return (false);
}
