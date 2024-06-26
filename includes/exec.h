/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:02 by yaharkat          #+#    #+#             */
/*   Updated: 2024/06/04 17:55:55 by obenchkr         ###   ########.fr       */
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
int		ft_exec_builtin(t_cmd *cmd, t_redir *io);
bool	ft_is_builtin(t_cmd *cmd);
int		ft_redirect(t_redir *io, bool is_builtin);
#endif
