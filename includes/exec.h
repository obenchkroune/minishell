/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 09:28:02 by yaharkat          #+#    #+#             */
/*   Updated: 2024/04/04 03:42:26 by yaharkat         ###   ########.fr       */
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

int		ft_exec_simple_cmd(t_node *tree);
int		ft_get_exit_status(int status);
int		ft_exec_node(t_node *tree);
int		ft_exec_pipeline(t_node *tree);
void	ft_exec_builtin(char **args);
bool	ft_is_builtin(char *cmd);
int		ft_redirect(t_io *io);
#endif
