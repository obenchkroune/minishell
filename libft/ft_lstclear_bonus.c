/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:31:44 by yaharkat          #+#    #+#             */
/*   Updated: 2024/02/29 14:06:43 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		if (*lst)
		{
			while (*lst)
			{
				temp = (*lst)->next;
				ft_lstdelone(*lst, del);
				*lst = temp;
			}
		}
		lst = NULL;
	}
}
