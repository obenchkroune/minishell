/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:36:34 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/28 02:40:30 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_input(char *input)
{
	t_token *tokens;
	t_token	*tokens_head;
	t_node	*tree;

	tokens = tokenize(input);
	tokens_head = tokens;
	tree = parse_pipe(&tokens);
	free_tokens(tokens_head);
	return (tree);
}
