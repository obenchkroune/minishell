/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:47:35 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/31 18:57:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_get_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '$')
		i++;
	if (str[i] == '?')
		return (ft_strdup("$?"));
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
		i++;
	return (ft_substr(str, 0, i));
}

static char	*replace_variable(char *str, char *name)
{
	char	*exit_status;

	if (name[1] == '?')
	{
		exit_status = ft_itoa(g_shell->last_exit_status);
		return ft_strreplace(str, name, exit_status);
	}
	else if (!get_env(name + 1))
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
	result = ft_strtrim(str, "\"'");
	if (str[0] == '\'')
		return (result);
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
