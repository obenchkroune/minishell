/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 02:09:09 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/08 02:24:55 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	pipe_exist_and_valid(void)
{
	return (ft_strrchr(g_shell->input, '|')
		&& is_empty(ft_strrchr(g_shell->input, '|') + 1));
}

bool	is_invalid_pipe(char *input)
{
	int		count;
	char	*pipe_p;

	pipe_p = ft_strrchr(g_shell->input, '|');
	if (!pipe_p)
		return (false);
	if (ft_strnstr(input, "|||", ft_strlen(input)))
		return (true);
	count = 0;
	while (*input)
	{
		if (*input == '|')
			count++;
		input++;
	}
	return (count > 2 && is_empty(pipe_p + 1));
}

int	handle_unclosed_pipe(void)
{
	char	*input_pipe_unclosed;
	char	*tmp;

	g_shell->inside_unclosed_pipe = true;
	if (is_invalid_pipe(g_shell->input))
		return (-2);
	if (pipe_exist_and_valid())
	{
		g_shell->has_unclosed_pipe = true;
		input_pipe_unclosed = readline(">");
		if (!input_pipe_unclosed)
			return (free(input_pipe_unclosed), -1);
		if (is_empty(input_pipe_unclosed))
		{
			if (handle_unclosed_pipe() < 2)
				return (free(input_pipe_unclosed), 2);
			return (free(input_pipe_unclosed), 0);
		}
		tmp = g_shell->input;
		g_shell->input = ft_strjoin(g_shell->input, input_pipe_unclosed);
		(free(input_pipe_unclosed), free(tmp));
		if (pipe_exist_and_valid())
			return (handle_unclosed_pipe());
	}
	return (0);
}

void	exit_eof(int status)
{
	if (status == -1)
		panic_minishell("syntax error: unexpected end of file", 2);
	else if (status == -2)
		panic_minishell("syntax error: unexpected '|'", 2);
	cleanup_rotation();
	if (status != -2)
	{
		cleanup_shell();
		ft_fprintf(STDOUT_FILENO, "exit\n");
	}
	if (status != -2 && status < 0)
		exit(2);
	else if (status != -2)
		exit(status);
}
