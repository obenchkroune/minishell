/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:02 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/18 12:55:57 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

typedef enum e_dir
{
	DIR_LEFT,
	DIR_RIGHT
}		t_dir;

int		ft_exec_simple_cmd(t_node *tree, bool is_pipe);
int		ft_get_exit_status(int status);
int		ft_exec_node(t_node *tree, bool is_pipe);
int		ft_exec_pipeline(t_node *tree);
void	ft_exec_builtin(t_cmd *cmd);
bool	ft_is_builtin(t_cmd *cmd);
int		ft_redirect(t_redir *io, bool is_builtin);
#endif
