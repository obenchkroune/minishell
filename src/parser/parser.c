#include "minishell.h"

t_node	*parse_input(char *input)
{
	t_lexer	lexer;

	lexer.cur = 0;
	lexer.input = input;
	return (parse_pipe(&lexer));
}
