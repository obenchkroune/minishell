/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:52:13 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/21 03:51:27 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_command(char *s)
{
	char	*start;

	start = s;
	while (*s && !ft_strchr(SYMBOLS, *s))
		s++;
	return ft_substr(start, 0, s - start);
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		panic("malloc");
	ft_bzero(token, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

char	*get_next_word(char *s)
{
	char	*start;

	skip_whitespace(&s);
	start = s;
	while (*s != '\0' && !ft_strchr(SYMBOLS WHITESPACE, *s))
		s++;
	return (ft_substr(start, 0, start - s));
}

t_token	*get_token(char *s)
{
	if (*s == '\0')
		return (NULL);
	else if (ft_strncmp(s, ">>", 2) == 0)
		return (create_token(get_next_word(s), T_APPEND));
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (create_token(get_next_word(s), T_HEREDOC));
	else if (ft_strncmp(s, "&&", 2) == 0)
		return (create_token("&&", T_AND));
	else if (ft_strncmp(s, "||", 2) == 0)
		return (create_token("||", T_OR));
	else if (*s == '>')
		return (create_token(get_next_word(s), T_REDIR_OUT));
	else if (*s == '<')
		return (create_token(get_next_word(s), T_REDIR_IN));
	else if (*s == '|')
		return (create_token("|", T_PIPE));
	else if (*s == ';')
		return (create_token(";", T_SEMICOL));
	else if (*s == '(')
		return (create_token("(", T_OPEN_PAREN));
	else if (*s == ')')
		return (create_token(")", T_CLOSE_PAREN));
	else
		return (create_token(get_command(s), T_COMMAND));
}

void	append_token(t_token **head, t_token *node)
{
	t_token	*tail;

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

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*curr_token;

	tokens = NULL;
	if (!input)
		return (NULL);
	while (1)
	{
		while (*input && ft_strchr(WHITESPACE, *input))
			input++;
		curr_token = get_token(input);
		if (!curr_token)
			break ;
		skip_whitespace(&input);
		input += ft_strlen(curr_token->value);
		append_token(&tokens, curr_token);
	}
	return (tokens);
}
