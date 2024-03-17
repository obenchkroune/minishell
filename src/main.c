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
		case N_REDIR:
			printf("N_REDIR (%s)\n", ((t_redir *)root)->file);
			print_tree(((t_redir *)root)->cmd, level + 1);
		default:
			break ;
	}
}

int	main(int argc, char const *argv[], char **envp)
{
	char	*input;
	t_tok	*tokens;
	pid_t	pid;

	(void)argc;
	(void)argv;
	(void)envp; // for now
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = tokenize(input);
		// t_tok *temp = tokens;
		// while (temp)
		// {
		// 	printf("%s (%d)\n", temp->value, temp->type);
		// 	temp = temp->next;
		// }
		pid = fork();
		if (pid == 0)
		{
			t_node *tree = parse_tree(&tokens);
			print_tree(tree, 0);
			exit(0);
		}
		wait(0);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}
