/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/25 22:58:15 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <libft.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include "parser.h"
# include "lexer.h"
# include "env.h"

typedef struct s_shell
{
	t_env	*env;
}	t_shell;

extern t_shell *shell;


void	panic(char *msg);
void	syntax_error(char *msg, char *cmd, ssize_t pos);
int		ft_isspace(int c);
bool	is_empty(char *str);
void	handle_sigint(int signal);
void	init_shell(char **envp);
void	cleanup_shell(void);
void	free_tab(char **tab);

#endif
