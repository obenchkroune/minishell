/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
/*   Updated: 2024/04/11 17:46:06 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define RED "\001\x1b[31m\002"
# define GREEN "\001\x1b[32m\002"
# define YELLOW "\001\x1b[33m\002"
# define BLUE "\001\x1b[34m\002"
# define MAGENTA "\001\x1b[35m\002"
# define CYAN "\001\x1b[36m\002"
# define RESET "\001\x1b[0m\002"

# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "history.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "signals.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_shell
{
	t_node			*tree;
	char			*input;
	size_t			lexer_idx;
	t_history		*history;
	char			*cwd;
	char			**envp;
	int				last_exit_status;
	char			last_exit_status_str[5];
	char			*prompt;
	bool			inside_unclosed_pipe;
	bool			has_unclosed_pipe;
	bool			has_syntax_error;
	bool			should_continue_execution;
	bool			has_heredoc;
	char			term_buffer[2048];
    char            *username;
    char            *hostname;
	struct termios	term;
}					t_shell;

extern t_shell		*g_shell;

void				panic(char *msg);
void				panic_minishell(char *msg, int status);
void				syntax_error(t_token token);
int					ft_isspace(int c);
bool				is_empty(char *str);
void				init_shell(char **envp);
void				cleanup_shell(void);
void				free_tab(char **tab);
void				cleanup_rotation(void);
char				*ft_strreplace(char *str, char *find, char *replace);
int					set_terminal_attributes(void);
bool				is_invalid_pipe(char *input);
int					handle_unclosed_pipe(void);
void				exit_eof(int status);
#endif
