#include "minishell.h"

t_shell *shell;

void	print_argv(char **argv)
{
	while (*argv)
	{
		printf(" - %s", *argv++);
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
			// print_argv(root->cmd->argv);
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

int main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	init_shell(envp);
	while (true)
	{
		input = readline("minishell$ ");
		if (!is_empty(input))
		{
			t_node	*node = parse_input(input);
			print_tree(node, 1);
			// execution
			free_tree(node);
			system("leaks minishell");
			free(input);
		}
	}
	cleanup_shell();
	return (EXIT_SUCCESS);
}
