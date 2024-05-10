/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:57 by obenchkr          #+#    #+#             */
/*   Updated: 2024/05/10 17:00:20 by obenchkr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool check_wildcard(char *pattern, char *string)
{
    if (*pattern == '\0' && *string == '\0')
        return (true);
    if (*string == '\0')
        return (false);
    if (*pattern == '*')
        return (check_wildcard(pattern, ++string) ||check_wildcard(++pattern, string));
    if (*pattern == *string)
        return (check_wildcard(++pattern, ++string));
    return (false);
}