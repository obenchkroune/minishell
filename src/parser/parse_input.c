/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 04:30:28 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/22 20:41:29 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_whitespace(char *input)
{
	char	*result;
	char	*temp;
	size_t	j;

	if (!input)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
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
	temp = result;
	result = ft_strtrim(result, "\t\v\r\f\b\n ");
	return (free(temp), result);
}

bool	is_duplicate_input(char *input)
{
	t_history	*last_history;

	last_history = get_histroy_tail();
	if (!last_history)
		return (false);
	return (ft_strcmp(last_history->value, input) == 0);
}

void	parse_input(void)
{
	char		*trimed_input;

	if (is_empty(g_shell->input))
	{
		g_shell->tree = NULL;
		return ;
	}
	g_shell->tree = parse_ast(false);
	trimed_input = trim_whitespace(g_shell->input);
	if (!g_shell->has_heredoc && !is_duplicate_input(trimed_input))
	{
		free(g_shell->input);
		g_shell->input = ft_strdup(trimed_input);
		add_history(g_shell->input);
		set_history(g_shell->input);
	}
	free(trimed_input);
}
