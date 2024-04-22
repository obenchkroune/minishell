/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:21:38 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/22 14:21:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
