/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:23:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/22 01:34:43 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_env(char *key, char *value)
{
	value = ft_strjoin(get_env(key), value);
	if (!value)
		panic("malloc");
	set_env(key, value);
	free(value);
}
