/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:36:34 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/31 19:46:46 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

bool	has_heredoc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->kind == T_DLESS)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}

t_node	*parse_input(char *input)
{
	t_token *tokens;
	t_token	*tokens_head;
	t_node	*tree;

	tokens = tokenize(input);
	if (!has_heredoc(tokens))
		add_history(g_shell->input);
	tokens_head = tokens;
	tree = parse_pipe(&tokens);
	free_tokens(tokens_head);
	return (tree);
}
