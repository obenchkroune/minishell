#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		panic("malloc");
	token->type = type;
	token->value = value;
	return (token);
}

static t_token	*cmd_token(t_lexer *l)
{
	size_t	start;
	size_t	len;

	start = l->cur;
	while (!ft_strchr("<>|&", l->input[l->cur]))
		l->cur++;
	len = l->cur - start;
	return (create_token(T_CMD, ft_substr(l->input, start, len)));
}

static char	*get_next_word(t_lexer *l)
{
	char	*pair_quote;
	size_t	start;

	while (ft_isspace(l->input[l->cur]))
		l->cur++;
	start = l->cur;
	if (ft_strchr("<>|&", l->input[start]) || l->input[start] == '\0')
		panic("syntax error");
	if (ft_strchr("'\"", l->input[l->cur]))
	{
		l->cur++;
		pair_quote = ft_strchr(l->input + l->cur, l->input[l->cur - 1]);
		if (!pair_quote)
			panic("syntax error: unclosed quote");
		l->cur = pair_quote - l->input + 1;
		return (ft_substr(l->input, start, l->cur - start));
	}
	while (l->input[l->cur] && !ft_strchr("<>|& \t", l->input[l->cur]))
		l->cur++;
	return (ft_substr(l->input, start, l->cur - start));
}

static t_token	*meta_token(t_lexer *l)
{
	char	*current;

	current = &l->input[l->cur];
	if (ft_strncmp(current, ">>", 2) == 0)
		return (l->cur += 2, create_token(T_APPEND, get_next_word(l)));
	else if (ft_strncmp(current, "<<", 2) == 0)
		return (l->cur += 2, create_token(T_HEREDOC, get_next_word(l)));
	else if (ft_strncmp(current, "||", 2) == 0)
		return (l->cur += 2, create_token(T_OR, NULL));
	else if (ft_strncmp(current, "&&", 2) == 0)
		return (l->cur += 2, create_token(T_AND, NULL));
	else if (*current == '>')
		return (l->cur++, create_token(T_OUT, get_next_word(l)));
	else if (*current == '|')
		return (l->cur++, create_token(T_PIPE, NULL));
	else if (*current == '<')
		return (l->cur++, create_token(T_IN, get_next_word(l)));
	return (NULL);
}

t_token	*get_next_token(t_lexer *l)
{
	while (ft_isspace(l->input[l->cur]))
		l->cur++;
	if (l->input[l->cur] == '\0')
		return (NULL);
	if (ft_strchr("<>|&", l->input[l->cur]))
		return (meta_token(l));
	return (cmd_token(l));
}
