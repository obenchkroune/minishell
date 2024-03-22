#include "minishell.h"

t_token	*get_next_token(t_lexer *l);

void	print_io(t_io *io, int level)
{
	while (io)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("io: %s\n", io->file);
		io = io->next;
	}
}

void	print_cmd(t_cmd *cmd, int level)
{
	int	j;

	j = 0;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("path: %s\n", cmd->path);
	while (cmd->argv[j])
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("argv[%d]: %s\n", j, cmd->argv[j]);
		j++;
	}
}

void	print_tree(t_node *root, int level)
{
	if (!root)
		return ;
	for (int i = 0; i < level; i++)
		printf("  ");
	if (root->type == N_CMD)
	{
		printf("=> N_CMD\n");
		print_cmd(root->cmd, level);
		print_io(root->io, level);
	}
	else if (root->type == N_PIPE)
		printf("=> N_PIPE\n");
	else if (root->type == N_AND)
		printf("=> N_AND\n");
	else if (root->type == N_OR)
		printf("=> N_OR\n");
	else
		printf("!! unknown\n");
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}


int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	// t_node	*parsed;

	(void)argc;
	(void)argv;
	(void)envp;
	while (true)
	{
		input = readline("minishell$ ");
		t_node *node = parse_input(input);
		print_tree(node, 0);
		free(input);
	}
	return EXIT_SUCCESS;
}
