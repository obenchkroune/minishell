/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:02:30 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 11:30:54 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	free_env(void)
{
	t_env	*next;
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		next = env->next;
		free(env);
		env = next;
	}
}

void	cleanup_shell(void)
{
	free_env();
	free(g_shell->cwd);
	g_shell->cwd = NULL;
	free_tab(g_shell->envp);
	g_shell->envp = NULL;
	g_shell->term.c_lflag |= ECHOCTL;
	free(g_shell->last_exit.str);
	if (tcsetattr(0, 0, &g_shell->term) == -1)
		perror("");
	ft_clear_history();
	free(g_shell);
	g_shell = NULL;
}

void	cleanup_rotation(void)
{
	free_tree(g_shell->tree);
	g_shell->tree = NULL;
	free(g_shell->input);
	g_shell->input = NULL;
	free(g_shell->prompt);
	g_shell->prompt = NULL;
	g_shell->has_syntax_error = false;
	g_shell->lexer_idx = 0;
	g_shell->has_heredoc = false;
}
