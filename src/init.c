/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:54:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 06:29:55 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (!shell)
		panic("malloc");
	shell->env = parse_env(envp);
}
