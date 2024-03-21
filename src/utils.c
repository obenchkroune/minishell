/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:09:36 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/19 05:28:04 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	skip_whitespace(char **str)
{
	while (**str && ft_strchr(WHITESPACE, **str))
		*str += 1;
}

void	panic(const char *msg)
{
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	exit(1);
}
