/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:18:16 by obenchkr          #+#    #+#             */
/*   Updated: 2024/06/14 11:56:14 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strreplace(char *str, char *find, char *replace)
{
	char	*result;
	size_t	len;
	char	*find_pos;

	if (!str)
		return (NULL);
	if (!find)
		return (ft_strdup(str));
	if (!replace)
		replace = "";
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
