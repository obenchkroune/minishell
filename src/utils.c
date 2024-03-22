#include "minishell.h"

void	panic(const char *msg)
{
	if (msg != NULL)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
