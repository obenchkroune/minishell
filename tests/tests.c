#include "minishell.h"

void	print_argv(char **argv);
void	print_tree(t_node *root, int level);
void	print_tab(char **tab);
void	print_io(t_io *io);

void	print_argv(char **argv)
{
	while (*argv)
	{
		printf(" - %s\n", *argv++);
	}
}

void	print_io(t_io *io)
{
	if (!io)
		printf("\tNO REDIRECTION\n");
	while (io)
	{
		printf("\tfile: %s\ttype:", io->file);
		switch (io->type) {
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
			printf(GREEN"CMD NODE"RESET);
			printf("\tEXEC_PATH: %s\n", root->cmd->path);
			print_io(root->io);
			print_argv(root->cmd->argv);
			break ;
		case N_PIPE:
			printf(BLUE"PIPE NODE\n"RESET);
			break ;
		default:
			printf(RED"UNKNOWN NODE\n"RESET);
			break ;
	}
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

