#ifndef _DEBUG_H

# define _DEBUG_H

# include <stdbool.h>
# include <stdio.h>
# include "parser.h"
# include "lexer.h"

void	print_io(t_io *io, int level);
void	print_cmd(t_cmd *cmd, int level);
void	print_tree(t_node *root, int level);
void	print_tokens(char *input);


#endif