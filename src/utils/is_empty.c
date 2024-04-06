/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:00:45 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/06 05:00:58 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_empty(char *str)
{
	if (!str)
	{
		printf("exit\n");
		ft_exit();
	}
	while (*str && ft_isspace(*str))
		str++;
	return (ft_strlen(str) == 0);
}
