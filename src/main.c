/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 05:10:23 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/31 19:50:21 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*g_shell;

void	print_argv(char **argv, int level);
void	print_tree(t_node *root, int level);
void	print_tab(char **tab);
void	print_io(t_io *io, int level);

int	main(int argc, char **argv, char **envp)
{
	(void)argc, (void)argv;
	init_shell(envp);
	while (true)
	{
		g_shell->input = readline("minishell$ ");
		if (!is_empty(g_shell->input))
		{
			g_shell->tree = parse_input(g_shell->input);
			print_tree(g_shell->tree, 0);
			// execution 🐱‍👤
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
		printf("\t(%d) %s\n", j + 1, argv[j]);
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
