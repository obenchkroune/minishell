/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:57:01 by obenchkr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/07 05:09:29 by yaharkat         ###   ########.fr       */
=======
/*   Updated: 2024/04/07 11:04:43 by obenchkr         ###   ########.fr       */
>>>>>>> prevent ctrl key symbol from being printed out!
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

# include "builtins.h"
# include "env.h"
# include "exec.h"
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
# include <unistd.h>
# include <termios.h>

typedef struct s_shell
{
	t_node			*tree;
	char			*input;
	size_t			lexer_idx;
	char			*cwd;
	char			**envp;
	int				last_exit_status;
	char			last_exit_status_str[5];
	char			*prompt;
	bool			has_syntax_error;
	bool			has_heredoc;
	char			term_buffer[2048];
	struct termios	term;
}				t_shell;

extern t_shell	*g_shell;

void			panic(char *msg);
void			panic_minishell(char *msg, int status);
void			syntax_error(t_token token);
int				ft_isspace(int c);
bool			is_empty(char *str);
void			init_shell(char **envp);
void			cleanup_shell(void);
void			free_tab(char **tab);
void			cleanup_rotation(void);
char			*ft_strreplace(char *str, char *find, char *replace);
int				set_terminal_attributes(void);

#endif
