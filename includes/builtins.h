/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:33:13 by yaharkat          #+#    #+#             */
/*   Updated: 2024/03/31 23:51:22 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>
# define NO_OLDPWD "cd: OLDPWD environment variable has not been set."
# define NO_HOME "cd: HOME environment variable has not been set."

void	ft_echo(char **args);
void	ft_cd(char **args);
void	ft_pwd(void);
void	ft_env(void);
void	ft_export(char **args);
void	ft_unset(char **args);
void	ft_exit(void);
bool	ft_is_builtin(char *cmd);
#endif