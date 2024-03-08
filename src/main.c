#include "minishell.h"
#include "lexer.h"

void	print_tokens(t_token *tokens);
void	handle_history(const char *input, t_token *token);

int	main(int argc, char const *argv[], char **envp)
{
	char	*input;
	t_token	*tokens;

	(void)argc;
	(void)argv;
	(void)envp; // for now
	while (1)
	{
		input = readline("minishell$ ");
		tokens = tokenize(input);
		handle_history(input, tokens);
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	return (0);
}

void	print_tokens(t_token *tokens)
{
	t_token *current = tokens;

	if (!has_valid_syntax(tokens))
	{
		printf("Invalid Syntax!\n");
		return ;
	}
	while (current != NULL)
	{
		printf("Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}

void	handle_history(const char *input, t_token *token)
{
	while (token)
	{
		if (token->type == T_HEREDOC)
			return ;
		token = token->next;
	}
	add_history(input);
}
