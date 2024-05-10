/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:30:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 18:02:44 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_input(void)
{
	char	*result;
	size_t	buf_size;
	char	*input;
	size_t	j;

	input = g_shell->input;
	buf_size = ft_strlen(input) + 1;
	result = malloc(sizeof(char) * buf_size);
	if (!result)
		panic("malloc");
	j = 0;
	while (*input)
	{
		if (j == 0 || (!ft_isspace(*input) || !ft_isspace(*(input - 1))))
		{
			if (ft_isspace(*input))
				result[j++] = ' ';
			else
				result[j++] = *input;
		}
		input++;
	}
	result[j] = '\0';
	free(g_shell->input);
	g_shell->input = result;
}

void	parse_input(void)
{
	if (is_empty(g_shell->input))
	{
		g_shell->tree = NULL;
		return ;
	}
	g_shell->tree = parse_pipe();
	if (!g_shell->has_heredoc)
	{
		trim_input();
		add_history(g_shell->input);
		set_history(g_shell->input);
	}
}
