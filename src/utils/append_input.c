/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:09:12 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_input(char *s1, char *s2)
{
	char	*value;

	s1 = ft_strjoin(s1, "\n");
	value = ft_strjoin(s1, s2);
	free(s1);
	return (value);
}
