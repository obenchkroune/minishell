#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "lexer.h"

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
		while (tokens)
		{
			printf("%s (%d)\n", tokens->value, tokens->type);
			tokens = tokens->next;
		}
		free_tokens(tokens);
		free(input);
		input = NULL;
	}
	return (0);
}
