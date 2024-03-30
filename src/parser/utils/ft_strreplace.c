/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:48:47 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/30 02:49:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strreplace(char *str, char *find, char *replace)
{
	size_t	len;
	char	*result;
	char	*find_ptr;

	len = ft_strlen(str) - ft_strlen(find) + ft_strlen(replace);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		panic("malloc");
	find_ptr = ft_strnstr(str, find, ft_strlen(str));
	if (!find_ptr)
		return (ft_strdup(str));
	ft_strlcat(result, str, find_ptr - str + 1);
	ft_strlcat(result, replace, len + 1);
	ft_strlcat(result, find_ptr + ft_strlen(find), len + 1);
	return (result);
}
