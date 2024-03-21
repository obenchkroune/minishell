#include "minishell.h"

void
	print_tree(t_node *root, int level)
{
	t_meta	*meta;
	t_redir	*redir;

	for (int i = 0; i < level; i++)
		printf("  ");
	switch (root->type)
	{
		case N_CMD:
			printf("cmd\n");
			break;
		case N_PIPE:
			printf("pipe\n");
			meta = (t_meta *)root;
			print_tree(meta->left, level + 1);
			print_tree(meta->right, level + 1);
			break ;
		case N_REDIR:
			redir = (t_redir *)root;
			printf("redir (%s)\n", redir->file);
			print_tree(redir->next, level + 1);
			break ;
		default:
			printf("not implemented\n");
	}
}

int
	main(int argc, char const *argv[], char **envp)
{
	char	*input;
	t_token	*tokens;

	(void)argc;
	(void)argv;
	(void)envp; // for now
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = tokenize(input);
		// while (tokens)
		// {
		// 	printf("%s (%d)\n", tokens->value, tokens->type);
		// 	tokens = tokens->next;
		// }
		t_node *node = parse(tokens);
		print_tree(node, 0);
		free(input);
	}
	return (0);
}
