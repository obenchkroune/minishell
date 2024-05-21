/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:21:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/21 03:20:10 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_redir(t_redir *redir)
{
	char	*expanded_file;

	if (!redir)
		return ;
	expand_redir(redir->next);
	expanded_file = ft_expand(redir->file);
	free(redir->file);
	redir->file = expanded_file;
}
