/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:47:35 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/30 09:01:48 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_get_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
		i++;
	return (ft_substr(str, 0, i));
}

static char	*replace_variable(char *str, char *name)
{
	if (!get_env(name + 1))
		return ft_strreplace(str, name, "");
	else if (ft_strlen(name) == 1)
		return ft_strreplace(str, name, "$");
	else
		return ft_strreplace(str, name, get_env(name + 1)->value);
}

char	*ft_expand(char *str)
{
	size_t	i;
	char	*result;
	char	*name;
	char	*temp;

	i = 0;
	result = ft_strdup(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			name = ft_get_name(str + i);
			temp = result;
			result = replace_variable(result, name);
			free(temp);
			free(name);
			i += ft_strlen(name);
		}
		else
			i += 1;
	}
	return (result);
}
