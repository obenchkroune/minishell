/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:52:13 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/17 09:10:38 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tok_type	get_tok_type(const char *s)
{
	if (*s == '\0')
		return (T_EOL);
	else if (ft_strncmp(s, ">>", 2) == 0)
		return (T_APPEND);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(s, "&&", 2) == 0)
		return (T_AND);
	else if (ft_strncmp(s, "||", 2) == 0)
		return (T_OR);
	else if (*s == '>')
		return (T_REDIR_OUT);
	else if (*s == '<')
		return (T_REDIR_IN);
	else if (*s == '|')
		return (T_PIPE);
	else if (*s == ';')
		return (T_SEMICOL);
	else if (*s == '(')
		return (T_OPEN_PAREN);
	else if (*s == ')')
		return (T_CLOSE_PAREN);
	else
		return (T_WORD);
}

static char	*increment_ptr(char **input, t_tok_type type)
{
	char	*start;
	char	*quote;

	start = *input;
	if (type == T_WORD)
	{
		if (ft_strchr("'\"", **input) != NULL)
		{
			quote = ft_strchr(*input + 1, **input);
			if (!quote)
				panic("Syntax error: unclosed quote");
			*input = quote + 1;
		}
		else
			while (**input != '\0' && !ft_strchr(SYMBOLS WHITESPACE, **input))
				*input += 1;
	}
	else if (
		type == T_HEREDOC || type == T_APPEND || type == T_OR || type == T_AND)
		*input += 2;
	else
		*input += 1;
	return (ft_substr(start, 0, *input - start));
}

t_tok	*create_token(char *value, t_tok_type type)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (!token)
		panic("malloc");
	ft_bzero(token, sizeof(t_tok));
	token->value = value;
	token->type = type;
	return (token);
}

void	append_token(t_tok **head, t_tok *node)
{
	t_tok	*tail;

	if (!head || !node)
		return ;
	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		tail = *head;
		while (tail->next)
			tail = tail->next;
		tail->next = node;
	}
}

t_tok	*get_next_token(char *input)
{
	char		*value;
	static char	*input_ptr;
	t_tok_type	type;

	if (input != NULL)
		input_ptr = input;
	if (!input_ptr)
		return (NULL);
	while (*input_ptr != '\0' && ft_strchr(WHITESPACE, *input_ptr))
		input_ptr++;
	if (*input_ptr == '\0')
		return (NULL);
	type = get_tok_type(input_ptr);
	if (type == T_EOL)
		return (NULL);
	value = increment_ptr(&input_ptr, type);
	return (create_token(value, type));
}
