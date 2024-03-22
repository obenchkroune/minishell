#include "debug.h"


void	print_io(t_io *io, int level)
{
	while (io)
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("file: %s\n", io->file);
		for (int i = 0; i < level; i++)
			printf("\t");
		switch (io->type)
		{
			case T_APPEND:
				printf("T_APPEND\n");
				break;
			case T_OUT:
				printf("T_OUT\n");
				break;
			case T_IN:
				printf("T_IN\n");
				break;
			case T_HEREDOC:
				printf("T_HEREDOC\n");
				break;
			default:
				printf("DEFAULT\n");
				break;
		}
		printf("\n");
		io = io->next;
	}
}

void	print_cmd(t_cmd *cmd, int level)
{
	int	j;

	j = 0;
	for (int i = 0; i < level; i++)
		printf("\t");
	printf("path: %s\n", cmd->path);
	while (cmd->argv[j])
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("argv[%d]: %s\n", j, cmd->argv[j]);
		j++;
	}
}

void	print_tree(t_node *root, int level)
{
	if (!root)
		return ;
	for (int i = 0; i < level; i++)
		printf("\t");
	if (root->type == N_CMD)
	{
		printf("=> N_CMD\n");
		print_cmd(root->cmd, level);
		print_io(root->io, level + 1);
	}
	else if (root->type == N_PIPE)
		printf("=> N_PIPE\n");
	else if (root->type == N_AND)
		printf("=> N_AND\n");
	else if (root->type == N_OR)
		printf("=> N_OR\n");
	else
		printf("!! unknown\n");
	printf("\n");
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}

void	print_tokens(char *input)
{
	t_lexer	lexer;
	t_token	*token;

	lexer.cur = 0;
	lexer.input = input;
	while (true)
	{
		token = get_next_token(&lexer);
		if (!token)
			break ;
		switch (token->type)
		{
			case T_CMD:
				printf("type: T_CMD, ");
				break ;
			case T_PIPE:
				printf("type: T_PIPE, ");
				break ;
			case T_AND:
				printf("type: T_AND, ");
				break ;
			case T_OR:
				printf("type: T_OR, ");
				break ;
			case T_APPEND:
				printf("type: T_APPEND, ");
				break ;
			case T_OUT:
				printf("type: T_OUT, ");
				break ;
			case T_IN:
				printf("type: T_IN, ");
				break ;
			case T_HEREDOC:
				printf("type: T_HEREDOC, ");
				break ;
			default:
				printf("type: UNKNOWN, ");
				break ;

		}
		printf("value: %s\n", token->value);
		free(token);
	}
}
