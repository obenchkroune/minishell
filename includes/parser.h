/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:53:11 by obenchkr          #+#    #+#             */
/*   Updated: 2024/03/09 23:13:02 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

typedef struct s_io_redirections
{
	char	*input;
	char	*output;
	int		input_fd;
	int		output_fd;
}	t_io_redirections;

typedef struct s_pipeline
{
	char				*executable;
	char				**args;
	t_io_redirections	*io_redirections;
	struct s_pipeline	*left;
	struct s_pipeline	*right;
}	t_pipeline;

#endif