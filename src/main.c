/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/12 16:07:34 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "env.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>

t_shell		*g_shell;

static char	*get_user_host_line(void)
{
	char	*result;
	size_t	len;
	size_t	color_len;

	color_len = ft_strlen(GREEN) + ft_strlen(RESET);
	len = color_len + ft_strlen(g_shell->username)
		+ ft_strlen(g_shell->hostname) + 3;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		panic("malloc");
	ft_strlcat(result, CYAN, len + 1);
	ft_strlcat(result, g_shell->username, len + 1);
	ft_strlcat(result, "@", len + 1);
	ft_strlcat(result, g_shell->hostname, len + 1);
	ft_strlcat(result, RESET ": ", len + 1);
	return (result);
}

static char	*get_display_line(void)
{
	char	*temp;
	char	*display_line;
	char	*user_host_line;

	user_host_line = get_user_host_line();
	temp = ft_strjoin(user_host_line, g_shell->cwd);
	free(user_host_line);
	display_line = ft_strjoin(temp, "$ ");
	free(temp);
	return (display_line);
}

static void	g_shell_checks_update(void)
{
	char	**new_input;
	char	*tmp;
	g_shell->inside_unclosed_pipe = false;
	g_shell->tree = parse_input();
	if (!g_shell->has_heredoc && g_shell->has_unclosed_pipe)
	{
		new_input = ft_split(g_shell->input, '|');
		tmp = ft_strtrim(new_input[0], " ");
		add_history(tmp);
		set_history(tmp);
		free_matrix(new_input);
		free(tmp);
	}
	else if (!g_shell->has_heredoc)
	{
		add_history(g_shell->input);
		set_history(g_shell->input);
	}
	if (!g_shell->has_syntax_error)
		ft_exec_node(g_shell->tree, false);
	g_shell->should_continue_execution = true;
}

int	main(int argc, char **argv, char **envp)
{
	int	check_status;

	(void)argc, (void)argv;
	init_shell(envp);
	signal_init();
	while (true)
	{
		cleanup_rotation();
		g_shell->prompt = get_display_line();
		g_shell->input = readline(g_shell->prompt);
		if (!g_shell->input)
			exit_eof(0);
		if (is_empty(g_shell->input))
			continue ;
		check_status = handle_unclosed_pipe();
		if (check_status < 0)
		{
			exit_eof(check_status);
			continue ;
		}
		g_shell_checks_update();
	}
	return (EXIT_SUCCESS);
}
