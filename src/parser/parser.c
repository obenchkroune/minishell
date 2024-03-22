/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 04:13:08 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/22 04:13:08 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_input(char *input)
{
	t_lexer	lexer;

	lexer.cur = 0;
	lexer.input = input;
	return (parse_pipe(&lexer));
}
