#include "minishell.h"
#include "debug.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	while (true)
	{
		input = readline("minishell$ ");
		if (!is_empty(input))
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				t_node *node = parse_input(input);
				print_tree(node, 0);
				free(input);
				exit(0);
			}
			wait(NULL);
		}
		free(input);
	}
	return EXIT_SUCCESS;
}
