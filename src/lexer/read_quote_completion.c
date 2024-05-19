/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quote_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 07:50:00 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/19 07:50:57 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define QUOTE_ERROR "syntax error: unexpected EOF while looking for matching"

bool	read_quote_completion(char quote)
{
	char	*input;
	char	*value;

	write(1, "> ", 2);
	input = get_next_line(g_shell->secondary_input);
	if (!input)
	{
		if (quote == '\'')
			syntax_error(QUOTE_ERROR " `''");
		else
			syntax_error(QUOTE_ERROR " `\"'");
		syntax_error("syntax error: unexpected end of file");
		return (false);
	}
	input[ft_strlen(input) - 1] = '\0';
	value = append_input(g_shell->input, input);
	(free(g_shell->input), free(input));
	g_shell->input = value;
	return (true);
}
