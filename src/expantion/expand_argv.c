/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:57:21 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/20 19:45:35 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_argv(char **argv)
{
	char	*arg;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		arg = ft_expand(argv[i]);
		free(argv[i]);
		argv[i] = arg;
		i++;
	}
	return (argv);
}
