/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 02:42:56 by yaharkat          #+#    #+#             */
/*   Updated: 2024/05/10 20:57:12 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_history
{
	char				*value;
	struct s_history	*next;
}						t_history;

t_history				*get_histroy_tail(void);
void					set_history(char *line);
void					ft_clear_history(void);
#endif