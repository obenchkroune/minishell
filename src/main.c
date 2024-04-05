/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/04 04:37:14 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*g_shell;

void		print_argv(char **argv, int level);
void		print_tree(t_node *root, int level);
void		print_tab(char **tab);
void		print_io(t_io *io, int level);

static char	*get_display_line(void)
{
	char		*line;
	static char	*display_line = NULL;

	free(display_line);
	line = ft_strjoin(GREEN "minishell@42:" RESET, g_shell->cwd);
	display_line = ft_strjoin(line, "$ ");
	free(line);
	return (display_line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*display_line;

	(void)argc, (void)argv;
	init_shell(envp);
	while (true)
	{
		display_line = get_display_line();
		g_shell->input = readline(display_line);
		if (!is_empty(g_shell->input))
		{
			g_shell->tree = parse_input(g_shell->input);
			// print_tree(g_shell->tree, 0);
			// execution 🐱‍👤
			ft_exec_node(g_shell->tree);
			cleanup_rotation();
		}
	}
	cleanup_shell();
	return (EXIT_SUCCESS);
}

void	print_argv(char **argv, int level)
{
	for (int j = 0; argv[j]; j++)
	{
		for (int i = 0; i < level + 1; i++)
			printf("\t");
		printf("\t(%d) %s\n", j, argv[j]);
	}
}

void	print_io(t_io *io, int level)
{
	for (int i = 0; i < level + 1; i++)
		printf("\t");
	if (!io)
		printf("\tNO REDIRECTION\n");
	while (io)
	{
		printf("\tfile: %s\ttype:", io->file);
		switch (io->type)
		{
		case IO_APPEND:
			printf("APPEND\n");
			break ;
		case IO_HEREDOC:
			printf("HEREDOC\n");
			break ;
		case IO_IN:
			printf("INPUT\n");
			break ;
		case IO_OUT:
			printf("OUTPUT\n");
			break ;
		}
		io = io->next;
	}
}

void	print_tree(t_node *root, int level)
{
	if (!root)
		return ;
	for (int i = 0; i < level; i++)
		printf(i == level - 1 ? "|-" : "\t");
	switch (root->type)
	{
	case N_CMD:
		printf(GREEN "CMD NODE" RESET);
		printf("\tEXEC_PATH: %s\n", root->cmd->path);
		print_io(root->io, level);
		print_argv(root->cmd->argv, level);
		break ;
	case N_PIPE:
		printf(BLUE "PIPE NODE\n" RESET);
		break ;
	default:
		printf(RED "UNKNOWN NODE\n" RESET);
		break ;
	}
	printf("\n");
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}

void	print_tab(char **tab)
{
	while (tab && *tab)
	{
		printf("- %s\n", *tab);
		tab++;
	}
}
