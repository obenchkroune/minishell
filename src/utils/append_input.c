/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:09:12 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/19 11:48:07 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_input(char *s1, char *s2)
{
	char	*value;

	s1 = ft_strjoin(s1, "\n");
	value = ft_strjoin(s1, s2);
	free(s1);
	return (value);
}