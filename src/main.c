#include "minishell.h"

void print_tree(t_node *root, int level)
{
	for (int i = 0; i < level; i++)
		printf("  ");
	switch (root->type)
	{
		case N_PIPE:
			printf("N_PIPE\n");
			print_tree(((t_pipe *)root)->left, level + 1);
			print_tree(((t_pipe *)root)->right, level + 1);
			break ;
		case N_EXEC:
			printf("N_EXEC\n");
			break ;
		default:
			break ;
	}
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp; // for now

	while (1)
	{
		input = readline("minishell$ ");
		t_tok *tokens = tokenize(input);
		t_node *tree = parse_tree(&tokens);
		print_tree(tree, 0);
		free_tokens(tokens);
		free(input);
		input = NULL;
	}
	return (0);
}
